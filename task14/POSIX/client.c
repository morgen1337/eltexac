#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#define N 10

int main(){
    int shmfd = shm_open("/shm", O_RDWR, 0666);
    ftruncate(shmfd, N);
    char *string = (char *)mmap(NULL, N, PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
    printf("%s\n", string);
    strcpy(string, "Hello!");
    shm_unlink("/shm");
    return 0;
}