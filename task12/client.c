#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    int fd;
    fd = open("fifo", O_RDONLY);
    char string[100];
    read(fd, string, 100);
    printf("%s", string);
    close(fd);
    return 0;
}