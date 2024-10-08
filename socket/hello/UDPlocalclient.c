#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define N 10

int main(){
    struct sockaddr_un addr;
    int server_socket = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (server_socket == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, "hello/UDPlocal");
    char msg[N] = "Hello!";
    char buf[N];
    if (sendto(server_socket, msg, N, 0, (struct sockaddr *) &addr, sizeof(addr)) == -1){
        perror("client sendto");
        exit(EXIT_FAILURE);
    }
    int client_struct_length = sizeof(addr);
    recvfrom(server_socket, buf, N, 0, (struct sockaddr *) &addr, &client_struct_length);
    printf("Message received from server: %s\n", buf);
    return 0;
}