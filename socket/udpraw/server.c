#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(){
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(7777);
    char msg[8];
    bind(fd, (struct sockaddr *) &addr, sizeof(addr));
    struct sockaddr_in clientaddr;
    socklen_t sizeofclientaddr = sizeof(clientaddr);
    recvfrom(fd, msg, 8, 0, (struct sockaddr *) &clientaddr, &sizeofclientaddr);
    printf("got message from raw client - %s\n", msg);
    msg[strlen(msg)+1] = '\0';
    msg[strlen(msg)] = '!';
    printf("%d\n", ntohs(clientaddr.sin_port));
    if (sendto(fd, &msg, sizeof(msg), 0, (struct sockaddr *) &clientaddr, sizeofclientaddr) == -1){
        perror("sendto");
        exit(EXIT_FAILURE);
    }
    return 0;
}