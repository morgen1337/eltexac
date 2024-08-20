#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    pid_t child_pid[6];

    child_pid[1] = fork();
    int status;

    if (child_pid[1] == 0)
    {
        child_pid[3] = fork();

        if (!child_pid[3])
        {
            printf("3th process, pid = %d, ppid = %d\n", getpid(), getppid());
        }
        else
        {
            child_pid[4] = fork();
            if (!child_pid[4])
            {
                printf("4th process, pid = %d, ppid = %d\n", getpid(), getppid());
            }
            else
            {
                wait(&status);
                wait(&status);
                printf("1st process, pid = %d, ppid = %d\n", getpid(), getppid());
            }
        }
    }
    else
    {
        wait(&status);
        child_pid[2] = fork();
        if (child_pid[2] == 0)
        {
            child_pid[5] = fork();
            if (!child_pid[5])
            {
                printf("5th process, pid = %d, ppid = %d\n", getpid(), getppid());
            }
            else
            {
                wait(&status);
                printf("2nd process, pid = %d, ppid = %d\n", getpid(), getppid());
            }
        }
        else
        {
            wait(&status);
            printf("Parent pid = %d, ppid = %d\n", getpid(), getppid());
        }
    }

    return 0;
}