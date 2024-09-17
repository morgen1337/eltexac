#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <string.h>
#include "vars.h"


int main(){
    mq_unlink("/myqr");
    mq_unlink("/myqs");
    int clientcount = 0;
    unsigned int prio;

    struct mq_attr attr;
    attr.mq_maxmsg = MAXQ;
    attr.mq_msgsize = sizeof(struct Chat);

    struct mq_attr attr2;
    attr2.mq_maxmsg = MAXQ;
    attr2.mq_msgsize = sizeof(struct usermessages);

    struct usermessages message;
    int messagecount;

    send = mq_open("/myqs", O_CREAT | O_WRONLY, 0666, &attr);
    if (send == -1){
        perror("Send mq_open");
        exit(-1);
    }
    receive = mq_open("/myqr", O_CREAT | O_RDONLY, 0666, &attr2);
    if (receive == -1){
        perror("Receive mq_open");
        exit(-1);
    }

    while (1){
        mq_receive(receive, (char*)&message, n, &prio);
        if (prio == 2){
            if (chat.clientcount < MAXQ){
                printf("Got client - %s!\n", message.username);
                strcpy(chat.usernames[chat.clientcount],message.username);
                chat.clientcount++;
            }
            else{
                printf("Not enough space for a new client!\n");
            }
        }
        else if (prio == 1){
            printf("%s: %s\n", message.username, message.msg);
            if (chat.nmessages < MAXQ){
                strcpy(chat.messages[chat.nmessages].username, message.username);
                strcpy(chat.messages[chat.nmessages++].msg, message.msg);
            }
            else{
                chat.nmessages = 0;
                strcpy(chat.messages[chat.nmessages].username, message.username);
                strcpy(chat.messages[chat.nmessages++].msg, message.msg);
            }
            
            }
            for (int i = 0; i < chat.clientcount; i++){
                if (mq_send(send, (char*)&chat, sizeof(struct Chat), 1) == -1)
                    perror("mq_send fail");
        }
        
    }

    
    mq_unlink("/myqr");
    mq_unlink("/myqs");
    mq_close(send);
    mq_close(receive);
    return 0;
}