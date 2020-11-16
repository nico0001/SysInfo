#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;
sem_t db //acces a la db
int readcount = 0; //nobre de readerss

sem_t rsem;

pthread_mutex_t z;
pthread_mutex_t mw;
int w = 0;

int ecritures = 0;
int lectures = 0;

void writer(void)
{
    while (ecritures < 640)
    {
        prepare_data(); //TODO

        pthread_mutex_lock(&mw);
        w++;
        if (w==1){
            sem_wait(&rsem);
        }
        pthread_mutex_unlock(&mw);

        sem_wait(&db);
        //section critique
        write_database(); //TODO
        ecritures ++;
        sem_post(&db);

        pthread_mutex_lock(&mw);
        w--;
        if (w==0){
            sem_post(&rsem);
        }
        pthread_mutex_unlock(&mw);

    }
    return;
}

void reader(void)
{
    while (lecutres < 2560)
    {
        pthread_mutex_lock(&z);
        sem_wait(&rsem);
        ptrhead_mutex_lock(&mutex);

        //section crtique
        readcount++;
        if (readcount == 1){
             //premier reader
             sem_wait(&db);
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&rsem);
        ptrhead_mutex_unlock(&z);

        read_database(); //TODO

        pthread_mutex_lock(&mutex);
        readcount--;
        if(readcount == 0){
            //départ du dernier reader
            sem_post(&db);
        }
        lectures++;
        pthread_mutex_unlock(&mutex);
        process_data(); //TODO        
    }
    return;
}



extern void lectEcr_problem(int nProds, int nCons) 
{
    sem_init(&rsem, NULL, 1);
    sem_init(&db, NULL, 1);

    //TODO

}
