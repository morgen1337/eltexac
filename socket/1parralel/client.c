#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int main(){
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(7776);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    int ret = connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret == -1){
        perror("connect 18");
        exit(EXIT_FAILURE);
    }
    int port;
    if (read(client_socket, &port, sizeof(port)) == -1)
        perror("read 25");
    close(client_socket);
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_port = htons(port);
    ret = connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret == -1){
        printf("   %d  \n", port);
        perror("connect 28");
        exit(EXIT_FAILURE);
    }
    printf("connected to port %d  \n", port);
    time_t mytime;
    read(client_socket, &mytime, sizeof(mytime));
    struct tm *now = localtime(&mytime);
    printf("Time: %d %d %d\n", now->tm_hour, now->tm_min, now->tm_sec);
    return 0;
}