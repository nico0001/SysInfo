#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include "tts.c"

int N;
int mutex;

void* testMutex(int N_thread){
    int i=0;
    while (i<6400/N_thread)
    {
        ttsLock(mutex);
        while(rand() > RAND_MAX/10000);
        ttsUnlock(mutex);
        i++;
    }
}

int main(int argc, char const *argv[])
{
    int mutex = ttsmutex_init();
    N = atoi(argv[1]);
    pthread_t thread_id[N];
    for (int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, testMutex, N);
    }
    for (int i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    ttsdestroy(mutex);

    return 0;
}
