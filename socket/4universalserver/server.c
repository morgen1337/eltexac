#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>
#include <sys/epoll.h>

#define Nservers 10
struct sockaddr_in clients[Nservers];

int port = 7778;

void *serverfuncTCP(void *arg){
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
    time_t mytime;
    for (int iterations = 0; iterations < 10; iterations++){
        mytime = time(NULL);
        write(client_socket, &mytime, sizeof(mytime));
        sleep(2);
    }
    close(client_socket);
    return NULL;
}

void *serverfuncUDP(void *arg){
    int *ind = (int *) arg;
    int i = *ind;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    while (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1){
        port++;
        server_addr.sin_port = htons(port);
        if (port > 9999){
            perror("bind 24");
            exit(EXIT_FAILURE);
        }
    }
    time_t mytime;
    for (int iterations = 0; iterations < 10; iterations++){
        mytime = time(NULL);
        sendto(server_socket, &mytime, sizeof(mytime), 0, (struct sockaddr *) &clients[i], sizeof(clients[i]));
        sleep(2);
    }
    free(arg);
    close(server_socket);
    return NULL;
}
int main(){
    pthread_t servers[Nservers];
    int serverquantity = 0;
    struct sockaddr_in listener;
    listener.sin_family = AF_INET;
    listener.sin_addr.s_addr = INADDR_ANY;
    listener.sin_port = htons(7776);
    int server_socketTCP = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    if (setsockopt(server_socketTCP, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1){
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    if (bind(server_socketTCP, (struct sockaddr *) &listener, sizeof(listener)) == -1){
        perror("bind 59");
        exit(EXIT_FAILURE);
    }
    if (listen(server_socketTCP, Nservers) == -1){
        perror("listen 63");
        exit(EXIT_FAILURE);
    }
    
    int server_socketUDP = socket(AF_INET, SOCK_DGRAM, 0);
    listener.sin_port = htons(6666);
    if (bind(server_socketUDP, (struct sockaddr *) &listener, sizeof(listener)) == -1){
        perror("bind 70");
        exit(EXIT_FAILURE);
    }
    int epoll_fd = epoll_create1(0);
    struct epoll_event ev, events[Nservers];
    ev.events = EPOLLIN;
    ev.data.fd = server_socketTCP;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socketTCP, &ev);
    ev.data.fd = server_socketUDP;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socketUDP, &ev);
    int udpclientsN = 0;
    char buf[10];
    while (1){
        int nfds = epoll_wait(epoll_fd, events, Nservers, -1);
        for (int i = 0; i < nfds; i++){
            if (events[i].data.fd == server_socketTCP){
                int client_socket = accept(server_socketTCP,NULL,NULL);
                if (client_socket == -1){
                    perror("client_socket");
                    exit(EXIT_FAILURE);
                }
                pthread_create(&servers[serverquantity++], NULL, serverfuncTCP, NULL);
                write(client_socket, &port, sizeof(int));
                close(client_socket);
            }
            if (events[i].data.fd == server_socketUDP){
                int sizze = sizeof(clients[udpclientsN]);
                recvfrom(server_socketUDP, &buf, 10, 0, (struct sockaddr *)&clients[udpclientsN], &sizze);
                int *ind = malloc(sizeof(int));
                *ind = udpclientsN++;
                pthread_create(&servers[serverquantity++], NULL, serverfuncUDP, (void *)ind);
            }
            printf("This port is busy now - %d, server - %d\n", port, serverquantity);
            port++;
        }
    
    if (serverquantity >= Nservers)
        break;
    }
    for (int i = 0; i < serverquantity; i++){
        pthread_join(servers[i], NULL);
    }
    close(server_socketTCP);
    return 0;

}