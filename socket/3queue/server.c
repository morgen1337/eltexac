#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#define Nservers 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct Linkedlist {
    struct Linkedlist *next;
    int client_port;
};

struct Linkedlist *queueforservers;

int n = 0;
int port = 7778;
int nserv = 0;

void *serverfunc(void *arg){
    nserv++;
    int servernum = nserv;
    sleep(5);
    int client_port;
    while (1){
    if (queueforservers){
    pthread_mutex_lock(&mutex);
    client_port = queueforservers->client_port;
    struct Linkedlist *next = queueforservers->next;
    if (next){
        free(queueforservers);
        queueforservers = next;
    }
    else
        queueforservers->client_port = -1;
    pthread_mutex_unlock(&mutex);
    if (client_port != -1){
        struct sockaddr_in client_addr;
        client_addr.sin_family = AF_INET;
        client_addr.sin_addr.s_addr = INADDR_ANY;
        client_addr.sin_port = htons(client_port);
        inet_pton(AF_INET, "127.0.0.1", &client_addr.sin_addr);
        int client_socket = socket(AF_INET, SOCK_STREAM, 0);
        connect(client_socket, (struct sockaddr *) &client_addr, sizeof(client_addr));
        printf("Server #%d connected to client on port: %d\n", servernum, client_port);
        time_t mytime = time(NULL);
        write(client_socket, &mytime, sizeof(mytime));
        close(client_socket);
    }
    }
    sleep(2);
    }
    
    return NULL;
}

int main(){
    struct Linkedlist *queue = malloc(sizeof(struct Linkedlist));
    queue->next = NULL;
    queue->client_port = -1;
    queueforservers = queue;
    struct sockaddr_in listener;
    listener.sin_family = AF_INET;
    listener.sin_addr.s_addr = INADDR_ANY;
    listener.sin_port = htons(7777);
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
    pthread_t servers[Nservers];
    printf("5 seconds to create a queue!\n"); //запустите клиентов, чтобы создать очередь
    for (int i = 0; i < Nservers; i++){
        pthread_create(&servers[i], NULL, serverfunc, NULL);
    }
    
    while (1){
    int client_socket = accept(server_socket,NULL,NULL);
    if (client_socket == -1){
        perror("client_socket");
        exit(EXIT_FAILURE);
    }
    read(client_socket, &queue->client_port, sizeof(int));
    queue->next = malloc(sizeof(struct Linkedlist));
    queue = queue->next;
    queue->next = NULL;
    queue->client_port = -1;
    n++;
    }
    for (int i = 0; i < Nservers; i++){
        pthread_join(servers[i], NULL);
    }
    return 0;

}