#include <stdio.h>
#define N 3

void arrayprint(int A[][N]){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int A[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            scanf("%d", &A[i][j]);
        }
    }
    arrayprint(A);
    return 0;
}