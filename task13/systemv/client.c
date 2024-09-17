#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#define N 10

struct msgbuf{
    long mtype;
    char mtext[N];
};

int main(){
    struct msgbuf msg;
    ssize_t received;
    struct msqid_ds buf;
    int d;
    d = msgget(ftok("systemv/server", 1), 0);
    if (d == -1){
        printf("No message queue is created!\n");
        exit(-1);
    }
    received = msgrcv(d, &msg, sizeof(msg.mtext), 0, 0);
    printf("Client - %s\n", msg.mtext);
    if (received){
        struct msgbuf msg2 = {1, "Hello!"};
        msgsnd(d, &msg2, sizeof(msg.mtext), 0);
    }
    return 0;
}