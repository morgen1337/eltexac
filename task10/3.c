#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void commandparser(char *command, char *program, char **arguments){
    int i = 0;
    int parserindex = 0;
    int word = 0;
    while (1){
        if (command[i] != ' ' && command[i] != '\0'){
            if (word == 0){
                program[parserindex] = command[i];
            }
            else{
                arguments[word][parserindex] = command[i];
            }
            parserindex++;
        }
        else {
            if (word == 0){
                program[parserindex] = '\0';
            }
            else{
                arguments[word][parserindex] = '\0';
            }
            parserindex = 0;
            word++;
        }
        if (command[i] == '\0')
            break;
        i++;
        
    }
    arguments[word] = NULL;
};

int main(){
    pid_t childpid;
    int status;
    
    char ch;
    int i;
    while(1) {
        char command[100];
        char program[100];
        char *arguments[100];
        for (int j = 0; j < 100; j++){
            arguments[j] = malloc(100 * sizeof(char));
        }
        i = 0;
        while ((ch = getchar()) != '\n' && i < 100) {
            command[i++] = ch;
        }
        command[i] = '\0';
        commandparser(command, program, arguments);
        if (strcmp(program, "exit") == 0)
            break;
        childpid = fork();
        if (!childpid){
            if (execvp(program, arguments) == -1){ // до меня дошло, что можно было обойтись без program, просто используя 0ой элемент в arguments, но я уже написал так и всё работает поэтому оставляю)
                perror("");
                exit(EXIT_FAILURE);
            }
        }
        else{
            wait(&status);
    }
    
            for (int j = 0; j < 100; j++){
        free(arguments[j]);
    }
    
    }
    
    return 0;
}