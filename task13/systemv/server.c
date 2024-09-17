#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define N 10

struct msgbuf{
    long mtype;
    char mtext[N];
};

int main(){
    struct msgbuf msg = {1, "Hi!"};
    struct msqid_ds buf;
    int d;
    d = msgget(ftok("systemv/server", 1), IPC_CREAT | 0666);
    msgsnd(d, &msg, sizeof(msg.mtext), 0);
    msgctl(d, IPC_STAT, &buf);
    while(buf.msg_qnum){
        msgctl(d, IPC_STAT, &buf);
    }
    if (buf.msg_qnum == 0){
        struct msgbuf msg2;
        msgrcv(d, &msg2, sizeof(msg.mtext), 0, 0);
        printf("Server - %s", msg2.mtext);
    }
    msgctl(d, IPC_RMID, &buf);
    return 0;
}