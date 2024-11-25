#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define N 10

int main(){
    struct sockaddr_in addr, client_addr;
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    if (bind(server_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        {
            perror("bind");
            exit(EXIT_FAILURE);
        }
    char msg[N] = "Hi!";
    char buf[N];
    int client_struct_length = sizeof(client_addr);
    recvfrom(server_socket, buf, N, 0, (struct sockaddr *) &client_addr, &client_struct_length);
    printf("Message received from client: %s\n", buf);
    if (sendto(server_socket, msg, N, 0, (struct sockaddr *)&client_addr, client_struct_length) == -1){
        perror("sendto");
    }
    close(server_socket);
    return 0;
}