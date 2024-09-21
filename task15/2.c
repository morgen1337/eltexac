#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static void sigusr1handler(int signum){
    printf("Got signal SIGUSR1");
    exit(0);
}

int main(){
    struct sigaction act;
    act.sa_handler = sigusr1handler;
    sigaction(SIGUSR1, &act, NULL);
    pid_t pid = getpid();
    mkfifo("fifo", 0666);
    int fd = open("fifo", O_RDWR);
    write(fd, &pid, sizeof(pid));

    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGINT);
    sigprocmask(SIG_BLOCK, &sigset, NULL);
    while(1){}
    return 0;
}