#include <stdio.h>

int main(){
    FILE *file = fopen("output.txt", "w+");
    fprintf(file, "String from file");
    for (int i = ftell(file) - 1; i >= 0; i--){
        fseek(file, i ,SEEK_SET);
        printf("%c", getc(file));
    }
    fclose(file);
    return 0;
}