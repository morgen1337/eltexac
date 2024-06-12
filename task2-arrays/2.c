#include <stdio.h>
#define N 5

void arrayprint(int A[]){
    for (int i = 0; i < N; i++){
        printf("%d ", A[i]);
    }
}

void revarr(int A[N]){
    int tmp;
    for (int i = 0; i < N / 2; i++){
        tmp = A[i];
        A[i] = A[N-1-i];
        A[N-1-i] = tmp;
    }
}

int main(){
    int A[N];
    for (int i = 0; i < N; i++){
        scanf("%d", &A[i]);
    }
    revarr(A);
    arrayprint(A);
    return 0;
}