#include <stdio.h>
#define N 5

void trianglefill(int A[][N]){
    int count0starter = N-1;
    for (int i = 0; i < N; i++){
        int count0 = count0starter;
        for (int j = 0; j < N; j++){
            if (count0){
                A[i][j] = 0;
                count0--;
            }
            else{
                A[i][j] = 1;
            }
        }
        count0starter--;
    }
}

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
    trianglefill(A);
    arrayprint(A);

    return 0;
}