#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define Nservers 10

int port = 7778;

void *serverfunc(void *arg){
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    while (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
        port++;
        server_addr.sin_port = htons(port);
        if (port > 9999){
            perror("bind 24");
            exit(EXIT_FAILURE);
        }
    }
    if (listen(server_socket, 2) == -1){
        perror("listen 28");
        exit(EXIT_FAILURE);
    }
    int client_socket = accept(server_socket,NULL,NULL);
    if (client_socket == -1){
        perror("client_socket");
        exit(EXIT_FAILURE);
    }
    time_t mytime = time(NULL);
    write(client_socket, &mytime, sizeof(mytime));
    close(client_socket);
    return NULL;
}

int main(){
    pthread_t servers[Nservers];
    int serverquantity = 0;
    struct sockaddr_in listener;
    listener.sin_family = AF_INET;
    listener.sin_addr.s_addr = INADDR_ANY;
    listener.sin_port = htons(7776);
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    if (bind(server_socket, (struct sockaddr *) &listener, sizeof(listener)) == -1){
        perror("bind 59");
        exit(EXIT_FAILURE);
    }
    if (listen(server_socket, Nservers) == -1){
        perror("listen 63");
        exit(EXIT_FAILURE);
    }
    int port2;
    while (1){
    int client_socket = accept(server_socket,NULL,NULL);
    if (client_socket == -1){
        perror("client_socket");
        exit(EXIT_FAILURE);
    }
    pthread_create(&servers[serverquantity], NULL, serverfunc, NULL);
    serverquantity++;
    printf("This port is busy now - %d, server - %d\n", port, serverquantity);
    write(client_socket, &port, sizeof(int));
    close(client_socket);
    port++;
    if (serverquantity >= Nservers)
        break;
    }
    for (int i = 0; i < serverquantity; i++){
        pthread_join(servers[i], NULL);
    }
    close(server_socket);
    return 0;

}