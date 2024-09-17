#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int main(){
    mqd_t fd = mq_open("/myq", O_RDWR);
    if (fd == -1) {
        printf("Error: no queue is found\n");
        exit(fd);
    }
    char str[257];
    unsigned int prio = 1;
    if (mq_receive(fd, str, 257, &prio) == -1) {
        perror("Error receiving message");
        exit(1);
    }
    printf("Client - %s\n", str);

    mqd_t fdr = mq_open("/myqr", O_RDWR);
    char str2[10] = "Hello!";
    if (mq_send(fdr, str2, 100, 1) == -1){
        perror("mq_send");
        exit(1);
    }

    mq_close(fd);


    return 0;
}