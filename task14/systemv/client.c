#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define N 10

int main(){
    key_t key = ftok("systemv/server", 1);
    int shmid = shmget(key, N, 0);
    if (shmid == -1){
        perror("shmget error");
    }
    char *string;
    string = (char *)shmat(shmid, NULL, 0);
    printf("%s", string);
    strcpy(string, "Hello!");
    shmdt((void*)string);
    return 0;
}