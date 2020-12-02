#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "tts.c"
#include "semTTS.c"

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
        ttsLock(write);
        if (ecritures == N_WRITTEN_ITEMS){
            ttsUnlock(write);
            //printf("fin write\n");
            pthread_exit(NULL);
        }
        ecritures ++;
        ttsUnlock(write);

        //augmenter le writecount
        ttsLock(writecount);
        wc++;
        //si c'est le premier writer
        if (wc == 1){
            semtts_wait(rsem);
        }
        ttsUnlock(writecount);

        //section critique: seulement un writer en meme temps
        semtts_wait(wsem);
        //printf("Writing\n");
        //write_database(); 
        while(rand() > RAND_MAX/10000);
        semtts_post(wsem);

        //diminuer le writecount
        ttsLock(writecount);
        wc--;
        if (wc == 0){
            semtts_post(rsem);
        }
        ttsUnlock(writecount);
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
        ttsLock(read);
        if (lectures == N_WRITTEN_ITEMS){
            ttsUnlock(read);
            //printf("fin read\n");
            pthread_exit(NULL);
        }
        lectures++;
        ttsUnlock(read);

        ttsLock(z);
        semtts_wait(rsem);

        ttsLock(readcount);
        //section crtique
        rc++;
        //c'est le premier reader
        if (rc == 1){
             semtts_wait(wsem);
        }
        ttsUnlock(readcount);
        semtts_post(rsem);
        ttsUnlock(z);

        //Lecture
        //read_database();
        //printf("Reading\n");
        while(rand() > RAND_MAX/10000);

        ttsLock(readcount);
        rc--;
        //départ du dernier reader
        if(rc == 0){
            semtts_post(wsem);
        }
        ttsUnlock(readcount);
        //process_data();        
    }
}



int main(int argc, char const *argv[])
{
    int nWriters = atoi(argv[1]);
    int nReaders = atoi(argv[2]);
   
    readcount = ttsmutex_init();
    writecount = ttsmutex_init();
    z = ttsmutex_init();
    write = ttsmutex_init();
    read = ttsmutex_init();
    rsem = semtts_init(1);
    wsem = semtts_init(1);

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
    ttsdestroy(readcount);
    ttsdestroy(writecount);
    ttsdestroy(z);
    ttsdestroy(write);
    ttsdestroy(read);
    semtts_destroy(rsem);
    semtts_destroy(wsem);

    return 0;
}
