#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 10

int main(){
    pid_t child_pid;
    int fd[2];
    pipe(fd);
    child_pid = fork();
    if (!child_pid){
        char buf[BUFSIZE];
        close(fd[1]);
        read(fd[0], buf, BUFSIZE);
        printf("%s", buf);
    }
    else{
        close(fd[0]);
        write(fd[1], "Hi!", sizeof("Hi!"));
        wait(NULL);
    }

    return 0;
}