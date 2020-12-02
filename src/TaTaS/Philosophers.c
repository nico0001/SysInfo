#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include "tts.c"
#include "semTTS.c"

#define THINKING 2
#define HUNGRY 3
#define EATING 4
#define LEFT (phnum + N - 1) % N
#define RIGHT (phnum + 1) % N
#define MAX_THREAD 8


int state[MAX_THREAD];
int N;
int phil[MAX_THREAD];


int S[MAX_THREAD];
int mutex;


void test_eat(int phnum) {
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[phnum] = EATING;
        // wake up hungry philosophers during putfork
        semtts_post(S[phnum]);
    }
} 
  
// take up chopsticks
void take_fork(int phnum){ 
    // critical section
    ttsLock(mutex);
    state[phnum] = HUNGRY;
    // eat if neighbours are not eating
    test_eat(phnum);
    ttsUnlock(mutex);
    // if unable to eat wait to be signalled 
    semtts_wait(S[phnum]);
}
  
// put down chopsticks 
void put_fork(int phnum) {
    // critical section
    ttsLock(mutex);
    state[phnum] = THINKING;
    // test neighbours
    test_eat(LEFT);
    test_eat(RIGHT);
    ttsUnlock(mutex);
} 
  
void* philosopher(void* num) {
    int* i = (int*) num;

    // loop 100 000 times for each philosopher
    for (int n = 100000; n!=0; n--) {
        take_fork(*i);
        put_fork(*i);
    }
    return num;
}

int main(int argc, char const *argv[])
{
    N = atoi(argv[1]);
    int i;
    pthread_t thread_id[N];
    // initialize the semaphores
    mutex = ttsmutex_init();
    for (i = 0; i < N; i++){
        S[i] = semtts_init(0);
    }
    for (i = 0; i < N; i++) {
        // create philosopher processes
        phil[i] = i;
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
    }
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    semtts_destroy(mutex);
    for (i = 0; i < N; i++)
        semtts_destroy(S[i]);
    
    return 0;
}