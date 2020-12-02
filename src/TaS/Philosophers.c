#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>
#include "test_and_set.c"
#include "semTS.c"

#define FALSE 0
#define TRUE 1
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
        //printf("Philosopher %d takes fork %d and %d\n", phnum, LEFT, phnum);
        //printf("Philosopher %d is Eating\n", phnum);
        // wake up hungry philosophers during putfork
        sem_post(S[phnum]);
    }
} 
  
// take up forks
void take_fork(int phnum){ 
    //section critique
    lock(mutex);
    state[phnum] = HUNGRY;
    //printf("Philosopher %d is Hungry\n", phnum);
    // eat if neighbours are not eating
    test_eat(phnum);
    unlock(mutex);
    // if unable to eat wait to be signalled 
    sem_wait(S[phnum]);
}
  
// put down forks 
void put_fork(int phnum) {
    //section critique
    lock(mutex);
    state[phnum] = THINKING;
    //printf("Philosopher %d putting fork %d and %d down\n", phnum, LEFT, phnum);
    //printf("Philosopher %d is thinking\n", phnum);
    test_eat(LEFT);
    
    test_eat(RIGHT);
    
    unlock(mutex);
} 
  
void* philosopher(void* num) {
    int* i = (int*) num;
    //printf("%d\n", *i);
    // loop +1 000 000 times for each philosopher if he is eating
    for (int n = 100000; n!=0; n--) {
        //printf("A %d %d\n", *i, n);
        take_fork(*i);
        //printf("B %d %d\n", *i, n);
        /*if (n<=200)
            printf("%d\n", *i);*/
        put_fork(*i);
        //printf("C %d %d\n", *i, n);
    }
    return num;
}

int main(int argc, char const *argv[])
{
    N = atoi(argv[1]);
    int i;
    pthread_t thread_id[N];
    // initialize the semaphores
    mutex = mutex_init();
    for (i = 0; i < N; i++){
        S[i] = sem_init(0);
    }
    for (i = 0; i < N; i++) {
        // create philosopher processes
        phil[i] = i;
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        //printf("Philosopher %d is thinking\n", i);
    }
    printf("création\n");
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
    printf("Join\n");
    destroy(mutex);
    for (i = 0; i < N; i++)
        sem_destroy(S[i]);
    
    printf("Philo done\n");
    return 0;
}