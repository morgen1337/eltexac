#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#define N 10

int main(){
    key_t key = ftok("systemv/server", 1);
    int shmid = shmget(key, N, IPC_CREAT | 0666);
    if (shmid == -1){
        perror("shmget error");
    }
    char *string;
    string = (char *)shmat(shmid, NULL, 0);
    strcpy(string, "Hi!\n");
    printf("EXECUTE THE CLIENT!\n");
    sleep(10); //время на запуск клиента
    printf("%s\n", string);
    shmdt((void*)string);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}