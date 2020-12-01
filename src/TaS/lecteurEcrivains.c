#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "test_and_set.c"
#include "semTS.c"

#define TRUE 1
#define N_WRITTEN_ITEMS 640
#define N_READ_ITEMS 2560

int write;
int read;
int z;
int readcount;
int writecount;

int wsem; //acces a la db
int rsem;

int wc = 0; //nbr des writers
int rc = 0; //nbr des readers

int ecritures = 0;//nombre des écritures
int lectures = 0; //nombre de lectures


void writer(void)
{
    while (TRUE)
    {
        //prepare_data();

        //Condition pour arrêter les écritures
        lock(write);
        if (ecritures == N_WRITTEN_ITEMS){
            unlock(write);
            //printf("fin write\n");
            pthread_exit(NULL);
        }
        ecritures ++;
        unlock(write);

        //augmenter le writecount
        lock(writecount);
        wc++;
        //si c'est le premier writer
        if (wc == 1){
            sem_wait(rsem);
        }
        unlock(writecount);

        //section critique: seulement un writer en meme temps
        sem_wait(wsem);
        //printf("Writing\n");
        //write_database(); 
        while(rand() > RAND_MAX/10000);
        sem_post(wsem);

        //diminuer le writecount
        lock(writecount);
        wc--;
        if (wc == 0){
            sem_post(rsem);
        }
        unlock(writecount);
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
        lock(read);
        if (lectures == N_WRITTEN_ITEMS){
            unlock(read);
            //printf("fin read\n");
            pthread_exit(NULL);
        }
        lectures++;
        unlock(read);

        lock(z);
        sem_wait(rsem);

        lock(readcount);
        //section crtique
        rc++;
        //c'est le premier reader
        if (rc == 1){
             sem_wait(wsem);
        }
        unlock(readcount);
        sem_post(rsem);
        unlock(z);

        //Lecture
        //read_database();
        //printf("Reading\n");
        while(rand() > RAND_MAX/10000);

        lock(readcount);
        rc--;
        //départ du dernier reader
        if(rc == 0){
            sem_post(wsem);
        }
        unlock(readcount);
        //process_data();        
    }
}



int main(int argc, char const *argv[])
{
    int nWriters = atoi(argv[1]);
    int nReaders = atoi(argv[2]);
   
    readcount = mutex_init();
    writecount = mutex_init();
    z = mutex_init();
    write = mutex_init();
    read = mutex_init();
    rsem = sem_init(1);
    wsem = sem_init(1);

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


    //Destruction mutex et sémaphores
    destroy(readcount);
    destroy(writecount);
    destroy(z);
    destroy(write);
    destroy(read);
    sem_destroy(rsem);
    sem_destroy(wsem);

    return 0;
}
