#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
    pid_t pid = getpid();
    mkfifo("fifo", 0666);
    int fd = open("fifo", O_RDWR);
    

    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigset, NULL);
    int sig;
    while(1){
        write(fd, &pid, sizeof(pid));
        sigwait(&sigset, &sig);
        printf("Got signal!\n");
    }
    return 0;
}