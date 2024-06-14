#include <stdio.h>
#define MAX 2048



char* main(){
    char string[MAX];
    int i = 0;
    printf("Enter a string: \n");
    while ((string[i] = getchar()) != '\n'){
        i++;
    }
    string[i] = '\0';

    int size = 0;
    char substring[MAX];
    printf("Enter a substring: \n");
    while ((substring[size] = getchar()) != '\n'){
        size++;
    }
    char *start = NULL;
    for (int search = 0, j = 0; search < i; search++){
        if (string[search] == substring[j]){
            if (j == 0)
                start = &string[search];
            j++;
        }
        if (j == size){
            printf("%s", start);
            return start;
        }
    }

    return start;
}