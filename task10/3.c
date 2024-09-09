#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define NSIZE 100

struct cmddata
{
    char program[NSIZE];
    char *arguments[NSIZE];
};

int commandparser(char *command, struct cmddata *cmd)
{
    int i = 0;
    int parserindex = 0;
    int word = 0;
    int ncmds = 0;
    while (1)
    {
        if (command[i] != ' ' && command[i] != '\0')
        {
            if (command[i] == '|')
            {
                cmd[ncmds].arguments[word] = NULL;
                ncmds++;
                word = 0;
                parserindex = -1;
            }
            else if (word == 0)
            {
                cmd[ncmds].program[parserindex] = command[i];
            }
            else
            {
                cmd[ncmds].arguments[word][parserindex] = command[i];
            }
            parserindex++;
        }
        else
        {
            if (parserindex != 0)
            {
                if (word == 0)
                {
                    cmd[ncmds].program[parserindex] = '\0';
                }
                else
                {
                    cmd[ncmds].arguments[word][parserindex] = '\0';
                }
                parserindex = 0;
                word++;
                cmd[ncmds].arguments[word] = malloc(NSIZE * sizeof(char));
            }
        }
        if (command[i] == '\0')
            break;
        i++;
    }
    cmd[ncmds].arguments[word] = NULL;
    ncmds++;
    return ncmds;
};

int main()
{
    pid_t childpid;
    int status;
    int fd[2];
    pipe(fd);
    char ch;
    int i;
    int ncmds;
    char command[NSIZE];
    struct cmddata cmd[NSIZE];
    for (int b = 0; b < NSIZE; b++)
    {   
        cmd[b].arguments[0] = malloc(NSIZE * sizeof(char));
    }
    while (1)
    {
        i = 0;
        while ((ch = getchar()) != '\n' && i < NSIZE)
        {
            command[i++] = ch;
        }
        command[i] = '\0';
        ncmds = commandparser(command, cmd);
        if (!strcmp(command, "exit") || !strcmp(command, "") )
            break;

        childpid = fork();
                if (!childpid){
                    close(fd[0]);
                    dup2(fd[1], STDOUT_FILENO);
                    if (execvp(cmd[0].program, cmd[0].arguments) == -1){
                        perror("");
                        exit(EXIT_FAILURE);
                    }
                }
                else{
                    wait(&status);
            }

        for (int j = 1; j < ncmds - 1; j++)
        {
                childpid = fork();
                if (!childpid){
                    dup2(fd[0], STDIN_FILENO);
                    dup2(fd[1], STDOUT_FILENO);
                    if (execvp(cmd[j].program, cmd[j].arguments) == -1){
                        perror("");
                        exit(EXIT_FAILURE);
                    }
                }
                else{
                    wait(&status);
            }
        }

        childpid = fork();
                if (!childpid){
                    close(fd[1]);
                    dup2(fd[0], STDIN_FILENO);
                    if (execvp(cmd[ncmds - 1].program, cmd[ncmds - 1].arguments) == -1){
                        perror("");
                        exit(EXIT_FAILURE);
                    }
                }
                else{
                    wait(&status);
            }
    }
    for (int b = 0; b < NSIZE; b++)
    {   
        free(cmd[b].arguments[0]);
    }

    return 0;
}