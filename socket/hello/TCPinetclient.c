#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define N 10

int main(){
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(6666);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    int ret = connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret == -1){
        perror("connect");
        exit(EXIT_FAILURE);
    }
    char msg[N] = "Hi!";
    write(client_socket, msg, N);
    char buf[N];
    read(client_socket, buf, N);
    printf("Got message from server: %s\n", buf);
    close(client_socket);
    return 0;
}