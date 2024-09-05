#include <stdio.h>
#include <pthread.h>

#define N 5

void *threadnum(void* arg){
    int *i = (int *)arg;
    printf("Thread num - %d\n", *i);
    return NULL;
}

int main(){
    pthread_t threads[N];
    int threadnumber[N];

    for (int i = 0; i < N; i++){
        threadnumber[i] = i;
        pthread_create(&threads[i], NULL, threadnum, (void *)&threadnumber[i]);
    }

    for (int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }

    return 0;
}