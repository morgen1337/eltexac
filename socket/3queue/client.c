#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int port = 7778;

int main(){
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7777);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    int ret = connect(server_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret == -1){
        perror("connect 18");
        exit(EXIT_FAILURE);
    }
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &client_addr.sin_addr);
    while (bind(client_socket, (struct sockaddr *) &client_addr, sizeof(client_addr)) == -1){
        port++;
        client_addr.sin_port = htons(port);
        if (port > 9999){
            perror("bind, no available ports");
            exit(EXIT_FAILURE);
        }
    }
    listen(client_socket, 1);
    write(server_socket, &port, sizeof(port));
    close(server_socket);
    printf("My port: %d\n", port);
    server_socket = accept(client_socket, NULL, NULL);
    time_t mytime;
    read(server_socket, &mytime, sizeof(mytime));
    struct tm *now = localtime(&mytime);
    printf("Time: %d %d %d\n", now->tm_hour, now->tm_min, now->tm_sec);
    return 0;
}