#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define N 10

int main(){
    struct sockaddr_un addr, client_addr;
    int server_socket = socket(AF_LOCAL, SOCK_DGRAM, 0);
    if (server_socket == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset(&addr, 0, sizeof(addr));
    memset(&client_addr, 0, sizeof(client_addr));
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, "loocalserversocket");
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
    client_addr.sun_family = AF_LOCAL;
    strcpy(client_addr.sun_path, "udpclient");
    if (sendto(server_socket, msg, N, 0, (struct sockaddr *)&client_addr, client_struct_length) == -1){
        perror("sendto");
    }
    close(server_socket);
    unlink("loocalserversocket");
    return 0;
}