#include <unistd.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h>

#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int state[8];
int phil[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };


sem_t S[8];
int N;
sem_t mutex;

void test(int phnum) {
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[phnum] = EATING;
        //printf("Philosopher %d takes fork %d and %d\n", phnum, LEFT, phnum);
        //printf("Philosopher %d is Eating\n", phnum);

        // wake up hungry philosophers during putfork
        sem_post(&S[phnum]);
    }
} 
  
// take up chopsticks
void take_fork(int phnum){ 
    sem_wait(&mutex);
    state[phnum] = HUNGRY;
    //printf("Philosopher %d is Hungry\n", phnum);
    // eat if neighbours are not eating
    test(phnum);
    sem_post(&mutex);
    // if unable to eat wait to be signalled 
    sem_wait(&S[phnum]);
}
  
// put down chopsticks 
void put_fork(int phnum) {
    sem_wait(&mutex);
    state[phnum] = THINKING;
    //printf("Philosopher %d putting fork %d and %d down\n", phnum, LEFT, phnum);
    //printf("Philosopher %d is thinking\n", phnum);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
} 
  
void* philosopher(void* num) {
    int n = 10000;
    // loop 10 000 times for each philosopher
    while (n!=0) {
        int* i = num;
        take_fork(*i);
        put_fork(*i);
        n--;
    }
    return num;
}
  
extern void philosopher_problem(int n_philo) {
    N = n_philo;
    int i;
    pthread_t thread_id[N];
    // initialize the semaphores
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++){
        sem_init(&S[i], 0, 0);
    }
    for (i = 0; i < N; i++) {
        phil[i]=i;
        // create philosopher processes
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        //printf("Philosopher %d is thinking\n", i);
    }
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    sem_destroy(&mutex);
    for (i = 0; i < 8; i++)
        sem_destroy(&S[i]);
    
    printf("Philo done\n");
}