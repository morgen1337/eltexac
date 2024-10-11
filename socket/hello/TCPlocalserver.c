#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>

#define N 10

int main(){
    struct sockaddr_un serv;
    char msg[N] = "Hi!";
    char buf[N];
    int server_socket;
    server_socket = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (!server_socket)
        perror("server_socket");    
    memset(&serv, 0, sizeof(serv));
    serv.sun_family = AF_LOCAL;
    strcpy(serv.sun_path, "localserversocket");
    if (bind(server_socket, (struct sockaddr *)&serv, sizeof(serv)) == -1){
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_socket, 1) == -1)
        perror("Listen");
    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == -1){
        perror("accept");
        exit(EXIT_FAILURE);
    }
    read(client_socket, buf, N);
    printf("message received from client: %s\n", buf);
    write(client_socket, msg, N);
    close(server_socket);
    unlink("localserversocket");
    return 0;
}