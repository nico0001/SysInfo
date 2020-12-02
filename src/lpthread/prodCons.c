#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define TRUE 1
#define False 0

#define BUFSIZE 8 //places dans le buffer
#define MAX_PROD 1024

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int buffer[BUFSIZE];
int in = 0;
int out = 0;
int producedItems = 0;
int consumedItems = 0;

void producer(void)
{
    int item;
    while(TRUE)
    {
        item = gen_random_int();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        //début: section critique
        if (producedItems >= MAX_PROD)
            break;
        buffer[in] = item;

        in = (in +1)%BUFSIZE;
        producedItems++;
        //fin: section critique

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        
        //attendre entre deux productions
        while(rand() > RAND_MAX/10000);
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    sem_post(&full);
    return;
}

//produces random int between INT_MIN et INT_MAX
int gen_random_int() {
    const int BITS_PER_RAND = (int)(log2(RAND_MAX/2 + 1) + 1.0); /* Or log(RAND_MAX + 1) / log(2) with older language standards */
    int ret = 0;
    for (int i = 0; i < sizeof(int) * CHAR_BIT; i += BITS_PER_RAND) {
        ret <<= BITS_PER_RAND;
        ret |= rand();
    }
    return ret;
}

void consumer(void)
{
    int item;
    while(TRUE)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        //début: section critique
        if (consumedItems>=MAX_PROD-1)
            break;
        item = buffer[out];
        buffer[out] = 0;
        out = (out+1)%BUFSIZE;
        consumedItems++;
        //fin: section critique
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        //attendre entre deux consommations
        while(rand() > RAND_MAX/10000);
    }
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
    sem_post(&empty);
    return;
}

int main(int argc, char const *argv[])
{
    int nProds = atoi(argv[1]);
    int nCons = atoi(argv[2]);

    pthread_t prod[nProds],  cons[nCons];
    //init du mutex et des sémaphores
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFSIZE);
    sem_init(&full, 0, 0);

    int a[nProds];
    int b[nCons];

    //creation des threads: producteurs
    for (int i = 0; i<nProds; i++)
    {
        pthread_create(&prod[i], NULL, (void *)producer, (void *)&a[i]);
    }

    //creation des threads: consommateurs
    for (int i = 0; i<nCons; i++)
    {
        pthread_create(&cons[i], NULL, (void *)consumer, (void *)&b[i]);
    }

    //attendre jusque toutes les threads ont fini
    for(int i = 0; i <nProds; i++)
    {
        pthread_join(prod[i], NULL);
    }

    for(int i = 0; i<nCons; i++)
    {
        pthread_join(cons[i], NULL);
    }

    //destruction du mutex et des sémaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("prodCons done\n");
    return 0;
}