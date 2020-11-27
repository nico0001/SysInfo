#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>

int N;
int mutex;

void* testMutex(int N_thread){
    int i=0;
    while (i<6400/N_thread)
    {
        lock(mutex);
        while(rand() > RAND_MAX/10000);
        unlock(mutex);
        i++;
    }
    
}

int main(int argc, char const *argv[])
{
    int mutex = mutex_init();
    N = atoi(argv[1]);
    pthread_t thread_id[N];
    printf("précréation\n");
    for (int i = 0; i < N; i++) {
        // create philosopher processes
        pthread_create(&thread_id[i], NULL, testMutex, N);
        //printf("Philosopher %d is thinking\n", i);
    }
    printf("création\n");
    for (int i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    destroy(mutex);

    return 0;
}
