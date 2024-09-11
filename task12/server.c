#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int fd;
    mkfifo("fifo", 0666);
    fd = open("fifo", O_WRONLY);
    char string[100] = "Hi!";
    write(fd, string, 100);
    close(fd);
    return 0;
}