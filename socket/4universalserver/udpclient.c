#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>

#define N 10

int main(){
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(6666);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    char msg[N] = "hi";
    sendto(server_socket, &msg, N, 0, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));
    time_t mytime;
    socklen_t addr_len = sizeof(serv_addr);
    for (int iterations = 0; iterations < 10; iterations++){
    recv(server_socket, &mytime, sizeof(mytime), 0);
    struct tm *now = localtime(&mytime);
    printf("Time: %d %d %d\n", now->tm_hour, now->tm_min, now->tm_sec);
    }
    return 0;
}