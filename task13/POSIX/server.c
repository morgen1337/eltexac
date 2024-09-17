#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

int main(){
    struct mq_attr attr;
    attr.mq_maxmsg = 1;
    attr.mq_msgsize = 256;
    mqd_t fd = mq_open("/myq", O_CREAT | O_RDWR, 0666, &attr);
    if (fd == -1) {
        perror("No queue is found");
        exit(fd);
    }
    char str[10] = "Hi!";
    if (mq_send(fd, str, 100, 1) == -1){
        perror("mq_send");
        exit(1);
    }

    mqd_t fdr = mq_open("/myqr", O_CREAT | O_RDWR, 0666, &attr);
    char str2[257];
    unsigned int prio = 1;
    if (mq_receive(fdr, str2, 257, &prio) == -1){
        perror("mq_receive");
        exit(1);
    }
    printf("Server - %s", str2);

    mq_close(fd);
    mq_unlink("/myq");


    return 0;
}