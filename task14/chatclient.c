#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <ncurses.h>
#include "vars.h"

sem_t *sem;
struct usermessages user;

int usernamecreate(){
    printw("Enter your name:");
    getstr(user.username);
    strcpy(chat->usernames[chat->clientcount], user.username);
    chat->clientcount++;
    for (int i = 0; i < chat->clientcount; i++)
            sem_post(sem);
    return 0;
}

void *printchat(void *arg){
    while (1){
        sem_wait(sem);
        clear();
        for (int i = 0; i < MAXQ; i++){
            if (i < chat->nmessages)
                mvprintw(i, 0, "%s: %s", chat->messages[i].username, chat->messages[i].msg);
            if (i < chat->clientcount)
                mvprintw(i, 50, "%s", chat->usernames[i]);
            
        }
        mvprintw(MAXQ + 1, MAXQ + 1, "%s:", user.username);
        printw("%s", user.msg);
        refresh();
    }
    return NULL;
}

int main(){
    int shmfd = shm_open(SHMNAME, O_RDWR, 0666);
    if (shmfd == -1){
        perror("shmfd failed");
    }
    chat = (struct Chat*)mmap(NULL, sizeof(struct Chat), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    if (chat == NULL){
        perror("chat alloc failed");
    }
    pthread_t thread;
    sem = sem_open("/sem", O_RDWR);
    initscr();
    pthread_create(&thread, NULL, printchat, NULL);
    usernamecreate();
    while (1){
        getstr(user.msg);
        if (chat->nmessages < MAXQ){
                strcpy(chat->messages[chat->nmessages].username, user.username);
                strcpy(chat->messages[chat->nmessages++].msg, user.msg);
            }
        else{
            chat->nmessages = 0;
            strcpy(chat->messages[chat->nmessages].username, user.username);
            strcpy(chat->messages[chat->nmessages++].msg, user.msg);
            }
        strcpy(user.msg, "");
        for (int i = 0; i < chat->clientcount; i++)
            sem_post(sem);
    }
    return 0;
}