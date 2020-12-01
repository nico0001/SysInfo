#include<stdio.h>

#define EXIST 1

int semList[2048];
int semMutexQueue[2048];
int semMutexCount[2048];
int exist[2048];

extern int sem_init(int n){
    int i = 0;
    while (i<2048){
        printf("%d\n", i);
        if (exist[i]==0){
            exist[i]=EXIST;
            semList[i] = n;
            semMutexQueue[i] = mutex_init();
            semMutexCount[i] = mutex_init();
            return i;
        }
        i++;
    }
    return -1;
}

extern void sem_wait(int indMutex){
    lock(semMutexCount[indMutex]);
    semList[indMutex]--;
    if(semList[indMutex]<0){
        unlock(semMutexCount[indMutex]);
        lock(semMutexQueue[indMutex]);
    }
    unlock(semMutexCount[indMutex]);
}

extern void sem_post(int indMutex){
    lock(semMutexCount[indMutex]);
    semList[indMutex]++;
    if(semList[indMutex]<=0){
        unlock(semMutexQueue[indMutex]);
    }
    else{
        unlock(semMutexCount[indMutex]);
    }
}

extern void sem_destroy(int indMutex){
    printf("mutex bien destroy\n");
    semList[indMutex]=0;
    exist[indMutex]=0;
    destroy(semMutexQueue[indMutex]);
    destroy(semMutexCount[indMutex]);
    semMutexQueue[indMutex]=0;
    semMutexCount[indMutex]=0;
}