#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define N 10

int main(){
    struct sockaddr_in server_addr, client_addr;
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1){
        perror("server socket");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(6666);
    if (bind(server_socket, (struct sockaddr *) server_socket, sizeof(server_socket)) == -1){
        perror("bind");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_socket, 1) == -1){
        perror("listen");
        exit(EXIT_FAILURE);
    }
    return 0;
}