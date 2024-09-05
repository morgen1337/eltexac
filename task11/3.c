#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define NBUYER 3
int shop[N];
int available[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int finished = 0;

void *shopping(void *args)
{
    int i;
    int *ind = (int *)args;
    int demand = (rand() % 10000) + 95000;
    while (1)
    {
        printf("Buyer %d Demand %d", *ind, demand);
        pthread_mutex_lock(&mutex);
        for (i = 0; i < N; i++)
        {
            if (available[i])
            {
                available[i] = 0;
                demand -= shop[i];
                printf(" - %d from shop %d", shop[i], i + 1);
                if (demand < 0)
                {
                    shop[i] = -demand;
                    demand = 0;
                    available[i] = 1;
                }
                else
                    shop[i] = 0;
                break;
            }
            // else
            //     available[i] = 1;
        }
        pthread_mutex_unlock(&mutex);

        if (!demand)
            break;

        printf("\n");
        sleep(2);
    }
    printf("\t\t\t\t!!Buyer %d finished\n", *ind);
    finished++;
    return NULL;
}

void *loaderfunc(void *args)
{
    int i, randq;
    while (1)
    {
        if (finished == NBUYER)
            break;
        pthread_mutex_lock(&mutex);
        for (i = 0; i < N; i++)
        {
            if (!available[i])
            {
                randq = (rand() % 2000) + 4000;
                shop[i] += randq;
                printf("\t\tShop %d delivery %d -> %d\n", i + 1, shop[i] - randq, shop[i]);
                available[i] = 1;
                break;
            }
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        shop[i] = (rand() % 4000) + 8000;
        available[i] = 1;
    }
    pthread_t buyer[NBUYER];
    int ind[NBUYER];
    pthread_t loader;

    printf("Shopping time!\n");

    for (int i = 0; i < NBUYER; i++)
    {
        ind[i] = i + 1;
        pthread_create(&buyer[i], NULL, shopping, (void *)&ind[i]);
    }
    pthread_create(&loader, NULL, loaderfunc, NULL);

    for (int i = 0; i < NBUYER; i++)
    {
        pthread_join(buyer[i], NULL);
    }
    pthread_join(loader, NULL);

    return 0;
}