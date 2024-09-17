#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <pthread.h>
#include <ncurses.h>
#include <string.h>
#include "vars.h"

struct usermessages user;


int sendusername(){
    printw("Enter your name: ");
    getstr(user.username);
    if (mq_send(send, (char*)&user, n, 2) == -1){
        perror("Username not sent:");
    }
    return 0;
}

void *getmessages(void *arg){
    unsigned int prio = 1;
    while (1){
        if (mq_receive(receive, (char*)&chat, sizeof(struct Chat), &prio) == -1)
            perror("Didnt get messages: ");
        clear();
        for (int i = 0; i < MAXQ; i++){
            if (i < chat.nmessages)
                printw("%s: %s", chat.messages[i].username, chat.messages[i].msg);
            if (i < chat.clientcount)
                mvprintw(i, 50, "%s\n", chat.usernames[i]);
            else
                printw("\n");
            
        }
        printw("\t%s:\n", user.username);
        printw("\t%s", user.msg);
        refresh();
        
    }

    return NULL;
}


int main(){
    send = mq_open("/myqr", O_WRONLY);
    if (send == -1){
        perror("Send mq_open");
        exit(-1);
    }
    receive = mq_open("/myqs", O_RDONLY);
    if (receive == -1){
        perror("Receive mq_open");
        exit(-1);
    }

    pthread_t getthr;
    
    initscr();

    pthread_create(&getthr, NULL, getmessages, NULL);

    sendusername();

    do{
        getstr(user.msg);
        if (mq_send(send, (char*)&user, n, 1) == -1)
            perror("couldnt send message");
        strcpy(user.msg,"");
    }while(1);

    pthread_join(getthr, NULL);

    mq_close(send);
    mq_close(receive);
    
    endwin();
    return 0;
}