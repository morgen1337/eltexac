#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define N 10

int main(){
    struct sockaddr_in addr, from;
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    char msg[N] = "Hello!";
    char buf[N];
    if (sendto(server_socket, msg, N, 0, (struct sockaddr *) &addr, sizeof(addr)) == -1){
        perror("client sendto");
        exit(EXIT_FAILURE);
    }
    int client_struct_length;
    if (recvfrom(server_socket, buf, N, 0, (struct sockaddr *) &from, &client_struct_length) == -1){
        perror("client recvfrom");
        exit(EXIT_FAILURE);
    }
    printf("Message received from server: %s\n", buf);
    close(server_socket);
    return 0;
}