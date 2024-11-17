#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

struct udpheader{
    uint16_t sourceport;
    uint16_t destport;
    uint16_t length;
    uint16_t checksum;
};

struct udpmsg{
    struct udpheader header;
    uint16_t msg[4];
};

int main(){
    struct udpmsg msg;
    msg.header.length = htons(sizeof(struct udpmsg));
    msg.header.destport = htons(7777);
    msg.header.sourceport = htons(7778);
    msg.header.checksum = 0;
    strcpy((char *)msg.msg, "Hello");
    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (fd == -1){
        perror("socket");
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
    uint8_t buf[1024];
    struct udpmsg *msg2;

    while(1){
        if (recv(fd, &buf, sizeof(buf), 0) == -1){
            perror("recv");
            exit(EXIT_FAILURE);
        }
        uint8_t offset = (buf[0] & 0x0F) * 4; //размер ip протокола который нужно пропустить
        msg2 = (struct udpmsg *)(buf + offset);
        if (ntohs(msg2->header.destport) == 7778){
            printf("message received - %s\n", (char *)msg2->msg);
            break;
        }
    }
    return 0;
}