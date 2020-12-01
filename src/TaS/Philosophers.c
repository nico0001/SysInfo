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


int S[MAX_THREAD];
int mutex;


void test_eat(int phnum) {
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING &&
    !left_hungry[phnum] && !right_hungry[phnum]) {
        state[phnum] = EATING;
        //printf("Philosopher %d takes fork %d and %d\n", phnum, LEFT, phnum);
        //printf("Philosopher %d is Eating\n", phnum);
        // wake up hungry philosophers during putfork
        sem_post(S[phnum]);
    }
} 
  
// take up chopsticks
void take_fork(int phnum){ 
    //section critique
    sem_wait(mutex);
    state[phnum] = HUNGRY;
    //printf("Philosopher %d is Hungry\n", phnum);
    // eat if neighbours are not eating
    test_eat(phnum);
    sem_post(mutex);
    // if unable to eat wait to be signalled 
    sem_wait(S[phnum]);
    right_hungry[LEFT]=FALSE;
    left_hungry[RIGHT]=FALSE;
}
  
// put down chopsticks 
void put_fork(int phnum) {
    //section critique
    sem_wait(mutex);
    state[phnum] = THINKING;
    //printf("Philosopher %d putting fork %d and %d down\n", phnum, LEFT, phnum);
    //printf("Philosopher %d is thinking\n", phnum);
    test_eat(LEFT);
    if(state[LEFT]==HUNGRY)
        left_hungry[phnum]=TRUE;
    test_eat(RIGHT);
    if(state[RIGHT]==HUNGRY)
        right_hungry[phnum]=TRUE;
    sem_post(mutex);
} 
  
void* philosopher(void* num) {
    int* i = (int*) num;
    left_hungry[*i]=FALSE;
    right_hungry[*i]=FALSE;
    //printf("%d\n", *i);
    // loop +1 000 000 times for each philosopher if he is eating
    for (int n = 10000; n!=0; n--) {
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
    mutex = sem_init(1);
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
    sem_destroy(mutex);
    for (i = 0; i < MAX_THREAD; i++)
        sem_destroy(S[i]);
    
    printf("Philo done\n");
    return 0;
}
/*
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
}*/