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
    while(producedItems < MAX_PROD)
    {
        item = gen_random_int();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        //début: section critique
        buffer[in] = item;
        //printf("Produced item %d\n", item);
        in = (in +1)%BUFSIZE;
        producedItems++;
        //fin: section critique

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        
        //wait between two productions
        while(rand() > RAND_MAX/10000);
    }
    //printf("Production finished\n");
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
    while(consumedItems<MAX_PROD-1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        //début: section critique
        item = buffer[out];
        buffer[out] = 0;
        //printf("Consumed item %d\n", item);
        out = (out+1)%BUFSIZE;
        consumedItems++;
        //fin: section critique
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        //wait between 2 consumptions
        while(rand() > RAND_MAX/10000);
    }
    //printf("Consumption finished\n");
    return;
}


extern void prodCons_problem(int nProds, int nCons) 
{
    pthread_t prod[nProds],  cons[nCons];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFSIZE);
    sem_init(&full, 0, 0);

    int a[nProds];
    int b[nCons];

    for (int i = 0; i<nProds; i++)
    {
        pthread_create(&prod[i], NULL, (void *)producer, (void *)&a[i]);
    }
    //printf("prods produced\n");

    for (int i = 0; i<nCons; i++)
    {
        pthread_create(&cons[i], NULL, (void *)consumer, (void *)&b[i]);
    }
    //printf("cons produced\n");

    for(int i = 0; i <nProds; i++)
    {
        pthread_join(prod[i], NULL);
    }
    //printf("prods joined\n");

    for(int i = 0; i<nCons; i++)
    {
        pthread_join(cons[i], NULL);
    }
    //printf("cons joined\n");

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("prodCons done\n");
    return;
}

