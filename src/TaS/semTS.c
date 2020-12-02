#include<stdio.h>

#define EXIST 1

int semList[2048];
int semMutexQueue[2048];
int semMutexCount[2048];
int exist[2048];

int sem_init(int n){
    int i = 0;
    while (i<2048){
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

void sem_wait(int indMutex){
    lock(semMutexCount[indMutex]);
    semList[indMutex]--;
    if(semList[indMutex]<0){
        unlock(semMutexCount[indMutex]);
        lock(semMutexQueue[indMutex]);
    }
    unlock(semMutexCount[indMutex]);
}

void sem_post(int indMutex){
    lock(semMutexCount[indMutex]);
    semList[indMutex]++;
    if(semList[indMutex]<=0){
        
        unlock(semMutexQueue[indMutex]);
    }
    unlock(semMutexCount[indMutex]);
}

void sem_destroy(int indMutex){
    semList[indMutex]=0;
    exist[indMutex]=0;
    destroy(semMutexQueue[indMutex]);
    destroy(semMutexCount[indMutex]);
    semMutexQueue[indMutex]=0;
    semMutexCount[indMutex]=0;
}