#include <stdio.h>

int main(int argc, char *argv[]){
    int i = 1;
    while(argv[i] != NULL){
        printf("%s\n", argv[i]);
        i++;
    }
    return 0;
}