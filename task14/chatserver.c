#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "vars.h"

int main(){
    shm_unlink(SHMNAME);
    sem_unlink("/sem");
    int shmfd = shm_open(SHMNAME, O_CREAT | O_RDWR, 0666);
    if (shmfd == -1){
        perror("shmfd failed");
    }
    ftruncate(shmfd, sizeof(struct Chat));
    sem_t *sem = sem_open("/sem", O_CREAT | O_RDWR, 0666, 0);
    while (1){
        sleep(10);
    }
    sem_close(sem);
    shm_unlink(SHMNAME);
    sem_unlink("/sem");
    return 0;
}