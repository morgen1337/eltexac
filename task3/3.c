#include <stdio.h>

int main(){
    int A[10] = {1,2,3,4,5,6,7,8,9,10};
    int *element = A;
    for (int i = 0; i < 10; i++){
        printf("%d ", *element);
        element++;
    }
    return 0;
}