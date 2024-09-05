#include <stdio.h>
#include <pthread.h>

#define N 4

long sum = 0;
long sumserial = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *sumf(void *arg){
    for (int i = 0; i < 4000000; i++){
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
    }

}

int main(){
    pthread_t threads[N];
    for (int i = 0; i < N; i++){
        pthread_create(&threads[i], NULL, sumf, NULL);
    }
    for (int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }
    printf("%ld\n", sum);

    for (int i = 0; i < 16000000; i++){
        sumserial++;
    }
    printf("%ld\n", sumserial);

    return 0;
}