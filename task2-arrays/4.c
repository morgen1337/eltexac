#include <stdio.h>
#define N 4

void snailfill(int A[N][N]){
    int imin = 0, jmin = 0, i = 0, j = 0;
    int imax = N-1, jmax = N-1;
    while (jmax - jmin >= 0 || imax - imin >= 0){
        for(j = jmin; j <= jmax; j++){
            scanf("%d", &A[imin][j]);
        }

        imin++;
        for(i = imin; i <= imax; i++){
            scanf("%d", &A[i][jmax]);
        }
        jmax--;
        for(j = jmax; j >= jmin; j--){
            scanf("%d", &A[imax][j]);
        }
        imax--;
        for (i = imax; i >= imin; i--){
            scanf("%d", &A[i][jmin]);
        }
        jmin++;
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
    snailfill(A);
    arrayprint(A);
    return 0;
}