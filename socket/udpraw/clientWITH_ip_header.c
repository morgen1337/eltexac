#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

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

struct udpheader{
    uint16_t sourceport;
    uint16_t destport;
    uint16_t length;
    uint16_t checksum;
};

struct udpmsg{
    struct ipheader ipheader;
    struct udpheader header;
    uint16_t msg[4];
};

int main(){
    struct udpmsg msg;
    msg.header.length = htons(sizeof(struct udpheader) + sizeof(msg.msg));
    msg.header.destport = htons(7777);
    msg.header.sourceport = htons(7778);
    msg.header.checksum = 0;
    msg.ipheader.saddr = 0;
    msg.ipheader.check = 0;
    msg.ipheader.saddr = 0;
    msg.ipheader.id = 0;
    msg.ipheader.protocol = 17;
    msg.ipheader.version = 4;
    msg.ipheader.ihl = 5;
    msg.ipheader.ttl = 255;
    msg.ipheader.frag_off=0;
    msg.ipheader.flags = 0;
    msg.ipheader.tos = 0;
    msg.ipheader.tot_len = htons(sizeof(struct ipheader) + sizeof(struct udpheader) + sizeof(msg.msg));
    inet_pton(AF_INET, "127.0.0.1", &(msg.ipheader.daddr));
    strcpy((char *)msg.msg, "Hello");
    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (fd == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    int on = 1;
    if (setsockopt(fd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) == -1){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 0;
    inet_pton(AF_INET, "127.0.0.1", &(addr.sin_addr.s_addr));
    if (sendto(fd, &msg, sizeof(msg), 0, (struct sockaddr *) &addr, sizeof(addr)) == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    while(1){
        if (recv(fd, &msg, sizeof(msg), 0) == -1){
            perror("recv");
            exit(EXIT_FAILURE);
        }
        if (ntohs(msg.header.destport) == 7778){
            printf("message received - %s\n", (char *)msg.msg);
            break;
        }
    }
    return 0;
}