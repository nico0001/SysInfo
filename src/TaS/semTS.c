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
            lock(semMutexQueue[i]);
            return i;
        }
        i++;
    }
    return -1;
}

void sem_wait(int id){
    
    lock(semMutexCount[id]);
    semList[id]--;
    if(semList[id]<0){
        unlock(semMutexCount[id]);
        lock(semMutexQueue[id]);
    }
    unlock(semMutexCount[id]);
}

void sem_post(int id){
    lock(semMutexCount[id]);
    semList[id]++;
    if(semList[id]<=0){
        unlock(semMutexQueue[id]);
    }
    else{
        unlock(semMutexCount[id]);
    }
}

void sem_destroy(int id){
    semList[id]=0;
    exist[id]=0;
    destroy(semMutexQueue[id]);
    destroy(semMutexCount[id]);
    semMutexQueue[id]=0;
    semMutexCount[id]=0;
}