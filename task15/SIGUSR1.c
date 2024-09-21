#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    pid_t pid;
    mkfifo("fifo", 0666);
    int fd = open("fifo", O_RDWR);
    read(fd, &pid, sizeof(pid));
    kill(pid, SIGUSR1);
    return 0;
}