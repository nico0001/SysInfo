#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define THINKING 2
#define HUNGRY 3
#define EATING 4
#define LEFT (phnum + N - 1) % N
#define RIGHT (phnum + 1) % N
#define MAX_THREAD 8


int state[MAX_THREAD];
int left_hungry[MAX_THREAD];
int right_hungry[MAX_THREAD];
int N;
int phil[MAX_THREAD];


sem_t S[MAX_THREAD];
pthread_mutex_t mutex;


void test_eat(int phnum) {
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING &&
    !left_hungry[phnum] && !right_hungry[phnum]) {
        state[phnum] = EATING;
        // wake up hungry philosophers during putfork
        sem_post(&S[phnum]);
    }
} 
  
// take up chopsticks
void take_fork(int phnum){ 
    // critical section
    pthread_mutex_lock(&mutex);
    state[phnum] = HUNGRY;
    // eat if neighbours are not eating
    test_eat(phnum);
    pthread_mutex_unlock(&mutex);
    // if unable to eat wait to be signalled 
    sem_wait(&S[phnum]);
    right_hungry[LEFT]=FALSE;
    left_hungry[RIGHT]=FALSE;
}
  
// put down chopsticks 
void put_fork(int phnum) {
    // critical section
    pthread_mutex_lock(&mutex);
    state[phnum] = THINKING;
    // test neighbours
    test_eat(LEFT);
    if(state[LEFT]==HUNGRY)
        left_hungry[phnum]=TRUE;
    test_eat(RIGHT);
    if(state[RIGHT]==HUNGRY)
        right_hungry[phnum]=TRUE;
    pthread_mutex_unlock(&mutex);
} 
  
void* philosopher(void* num) {
    int* i = (int*) num;
    left_hungry[*i]=FALSE;
    right_hungry[*i]=FALSE;
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
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < N; i++){
        sem_init(&S[i], 0, 0);
    }
    for (i = 0; i < N; i++) {
        // create philosopher processes
        phil[i] = i;
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    pthread_mutex_destroy(&mutex);
    for (i = 0; i < N; i++)
        sem_destroy(&S[i]);
    
    return 0;
}