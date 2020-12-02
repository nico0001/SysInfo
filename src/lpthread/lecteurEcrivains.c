#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define TRUE 1
#define N_WRITTEN_ITEMS 640
#define N_READ_ITEMS 2560

pthread_mutex_t write;
pthread_mutex_t read;
pthread_mutex_t z;
pthread_mutex_t readcount;
pthread_mutex_t writecount;

sem_t wsem;
sem_t rsem; 

int wc = 0; //nbr des écrivains
int rc = 0; //nbr des lecteurs

int ecritures = 0;//nombre des écritures
int lectures = 0; //nombre de lectures


void writer(void)
{
    while (TRUE)
    {

        //Condition pour arrêter les écritures
        pthread_mutex_lock(&write);
        if (ecritures == N_WRITTEN_ITEMS){
            pthread_mutex_unlock(&write);
            pthread_exit(NULL);
        }
        ecritures ++;
        pthread_mutex_unlock(&write);

        //augmenter le writecount
        pthread_mutex_lock(&writecount);
        wc++;
        //si c'est le premier writer
        if (wc == 1){
            sem_wait(&rsem);
        }
        pthread_mutex_unlock(&writecount);

        //section critique: 
        //seulement un writer en meme temps a accès
        sem_wait(&wsem);
        //write: 
        while(rand() > RAND_MAX/10000);
        sem_post(&wsem);

        //diminuer le writecount
        pthread_mutex_lock(&writecount);
        wc--;
        if (wc == 0){
            sem_post(&rsem);
        }
        pthread_mutex_unlock(&writecount);
    }
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

void reader(void)
{
    while (TRUE)
    {
        //condition pour arrêter les lectures
        pthread_mutex_lock(&read);
        if (lectures == N_WRITTEN_ITEMS){
            pthread_mutex_unlock(&read);
            pthread_exit(NULL);
        }
        lectures++;
        pthread_mutex_unlock(&read);

        
        pthread_mutex_lock(&z);
        sem_wait(&rsem);

        pthread_mutex_lock(&readcount);
        //section crtique:
        rc++;
        //si c'est le premier reader
        if (rc == 1){
             sem_wait(&wsem);
        }
        pthread_mutex_unlock(&readcount);
        sem_post(&rsem);
        pthread_mutex_unlock(&z);

        //Lecture
        while(rand() > RAND_MAX/10000);

        pthread_mutex_lock(&readcount);
        rc--;

        //départ du dernier reader
        if(rc == 0){
            sem_post(&wsem);
        }
        pthread_mutex_unlock(&readcount);        
    }
}



int main(int argc, char const *argv[])
{
    int nWriters = atoi(argv[1]);
    int nReaders = atoi(argv[2]);
   
   //init des mutex et sémaphores
    pthread_mutex_init(&readcount, NULL);
    pthread_mutex_init(&writecount, NULL);
    pthread_mutex_init(&z, NULL);
    pthread_mutex_init(&write, NULL);
    pthread_mutex_init(&read, NULL);
    sem_init(&rsem, 0, 1);
    sem_init(&wsem, 0, 1);

    pthread_t writers[nWriters];
    pthread_t readers[nReaders];

    //Creation writers et readers
    for (int i = 0; i<nWriters; i++){
        pthread_create(&writers[i], NULL, (void*)writer, NULL);
    }
    printf("writer created\n");

    for (int i = 0; i<nReaders; i++){
        pthread_create(&readers[i], NULL, (void*)reader, NULL);
    }
    printf("reader created\n");


    //Finalisation des writers et readers 
    for (int i = 0; i< nWriters; i++){
        pthread_join(writers[i], NULL);
    }
    printf("writers done\n");

    for (int i = 0; i<nReaders; i++){
        pthread_join(readers[i],NULL);
    }
    printf("readers done\n");


    //Déstruction mutex et sémaphores
    pthread_mutex_destroy(&readcount);
    pthread_mutex_destroy(&writecount);
    pthread_mutex_destroy(&z);
    pthread_mutex_destroy(&write);
    pthread_mutex_destroy(&read);
    sem_destroy(&rsem);
    sem_destroy(&wsem);

    return 0;
}
