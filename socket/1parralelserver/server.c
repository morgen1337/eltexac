#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define Nservers 10

struct Servinfo{
    int port;
    int free;
    };
struct Servinfo servinfo[Nservers];

void *serverfunc(void *arg){
    int *ind = (int *) arg;
    int i = *ind;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(servinfo[i].port);
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    while (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
        servinfo[i].port++;
        server_addr.sin_port = htons(servinfo[i].port);
        if (servinfo[i].port > 9999){
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
    servinfo[i].free = 0;
    time_t mytime = time(NULL);
    write(client_socket, &mytime, sizeof(mytime));
    close(client_socket);
    servinfo[i].free = 0;
    free(arg);
    return NULL;
}

int main(){
    pthread_t servers[Nservers];
    int *tmp;
    for (int i = 0; i < Nservers; i++){
        servinfo[i].port = 7778 + i;
        servinfo[i].free = 1;
        tmp = malloc(sizeof(int));
        *tmp = i;
        pthread_create(&servers[i], NULL, serverfunc, (void *)tmp);
    }
    struct sockaddr_in listener;
    listener.sin_family = AF_INET;
    listener.sin_addr.s_addr = INADDR_ANY;
    listener.sin_port = htons(7777);
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(server_socket, (struct sockaddr *) &listener, sizeof(listener)) == -1){
        perror("bind 59");
        exit(EXIT_FAILURE);
    }
    if (listen(server_socket, Nservers) == -1){
        perror("listen 63");
        exit(EXIT_FAILURE);
    }
    printf("\n");
    for (int i = 0; i < Nservers; i++){
        printf("%d - %d\n", i, servinfo[i].port);
    }
    while (1){
    int client_socket = accept(server_socket,NULL,NULL);
    if (client_socket == -1){
        perror("client_socket");
        exit(EXIT_FAILURE);
    }
    int iffree = 0;
    for (int i = 0; i < Nservers; i++){
        if (servinfo[i].free){
            printf("This port is busy - %d, server - %d\n", servinfo[i].port, i);
            write(client_socket, &servinfo[i].port, sizeof(servinfo[i].port));
            close(client_socket);
            iffree = 1;
            break;
        }
    }
    if (!iffree){
        write(client_socket, &iffree, sizeof(int));
        break;
    }
    }
    for (int i = 0; i < Nservers; i++){
        pthread_join(servers[i], NULL);
    }
    return 0;

}