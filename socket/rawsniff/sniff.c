#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (fd == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }
    char buf[10];
    int size;
    while (1){
        size = recv(fd, &buf, 10, 0);
        if (size == -1){
            perror("recv");
            exit(EXIT_FAILURE); 
        }
        printf("package received\n");
        for (int i = 0; i < size; i++){
            for (int j = 7; j >= 0; j--)
                printf("%d", (buf[i] >> j) & 1);
            printf(" ");
        }
        printf("\n");
    }
    return 0;
}