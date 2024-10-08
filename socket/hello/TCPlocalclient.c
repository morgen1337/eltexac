#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <unistd.h>

#define N 10

int main(){
    struct sockaddr_un addr;
    int client_socket;
    char msg[N] = "Hello!";
    char buf[N];
    client_socket = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (client_socket == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, "hello/localserversocket");
    if (connect(client_socket, (struct sockaddr *) &addr, sizeof(addr)) == -1)
        {
            perror("connect");
            exit(EXIT_FAILURE);
        }
    write(client_socket, msg, sizeof(msg));
    read(client_socket, buf, N);
    printf("message received from server: %s\n", buf);
    return 0;
}