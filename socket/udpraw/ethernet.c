#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <net/ethernet.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

struct ethheader {
    uint8_t dest_mac[6];
    uint8_t src_mac[6];
    uint16_t ethertype;
};

struct udpheader {
    uint16_t sourceport;
    uint16_t destport;
    uint16_t length;
    uint16_t checksum;
};

struct ipheader {
    uint8_t ihl:4, version:4;
    uint8_t tos;
    uint16_t tot_len;   
    uint16_t id;
    uint16_t frag_off:13, flags:3;
    uint8_t ttl;
    uint8_t protocol;
    uint16_t check;
    uint32_t saddr;
    uint32_t daddr;
};

struct udpmsg {
    struct ethheader ethheader;
    struct ipheader ipheader;
    struct udpheader udpheader;
    char payload[64];
};


unsigned short calculate_checksum(unsigned short *buffer, int length) {
    unsigned long sum = 0;
    while (length > 1) {
        sum += *buffer++;
        length -= 2;
    }
    if (length == 1) {
        sum += *(unsigned char *)buffer;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return ~sum;
}

int main() {
    struct udpmsg msg;
    memset(&msg, 0, sizeof(msg));

    uint8_t dest_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    uint8_t src_mac[6] = {0x02, 0x42, 0xAC, 0x11, 0x00, 0x02};
    memcpy(msg.ethheader.dest_mac, dest_mac, 6);
    memcpy(msg.ethheader.src_mac, src_mac, 6);
    msg.ethheader.ethertype = htons(ETH_P_IP); 

    msg.udpheader.sourceport = htons(7778);
    msg.udpheader.destport = htons(7777);
    msg.udpheader.length = htons(sizeof(struct udpheader) + sizeof(msg.payload));
    msg.udpheader.checksum = 0;

    msg.ipheader.version = 4;
    msg.ipheader.ihl = 5;
    msg.ipheader.tos = 0;
    msg.ipheader.tot_len = htons(sizeof(struct ipheader) + sizeof(struct udpheader) + sizeof(msg.payload));
    msg.ipheader.id = htons(54321);
    msg.ipheader.frag_off = 0;
    msg.ipheader.flags = 0;
    msg.ipheader.ttl = 64;
    msg.ipheader.protocol = IPPROTO_UDP;
    inet_pton(AF_INET, "192.168.1.1", &msg.ipheader.saddr);
    inet_pton(AF_INET, "192.168.1.255", &msg.ipheader.daddr);

    strcpy(msg.payload, "Hello");

    msg.ipheader.check = calculate_checksum((unsigned short *)&msg.ipheader, sizeof(struct ipheader));

    int sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_ll dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sll_family = AF_PACKET;
    dest_addr.sll_protocol = htons(ETH_P_IP);
    dest_addr.sll_halen = 6;
    memcpy(dest_addr.sll_addr, dest_mac, 6);

    if (sendto(sockfd, &msg, sizeof(msg), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) == -1) {
        perror("sendto");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        char buffer[2048];
        ssize_t recv_len = recv(sockfd, buffer, sizeof(buffer), 0);
        if (recv_len == -1) {
            perror("recv");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        struct ethheader *recv_eth = (struct ethheader *)buffer;
        if (ntohs(recv_eth->ethertype) == ETH_P_IP) {
            struct ipheader *recv_ip = (struct ipheader *)(buffer + sizeof(struct ethheader));
            struct udpheader *recv_udp = (struct udpheader *)(buffer + sizeof(struct ethheader) + sizeof(struct ipheader));
            char *recv_payload = (char *)(buffer + sizeof(struct ethheader) + sizeof(struct ipheader) + sizeof(struct udpheader));

            if (ntohs(recv_udp->destport) == 7778) {
                printf("Received reply: %s\n", recv_payload);
                break;
            }
        }
    }

    close(sockfd);
    return 0;
}
