#include<stdio.h>

#define EXIST 1

int semList[2048];
int semMutexQueue[2048];
int semMutexCount[2048];
int exist[2048];

int semtts_init(int n){
    int i = 0;
    while (i<2048){
        if (exist[i]==0){
            //printf("%d\n", i);
            exist[i]=EXIST;
            semList[i] = n;
            semMutexQueue[i] = ttsmutex_init();
            semMutexCount[i] = ttsmutex_init();
            ttsLock(semMutexQueue[i]);
            return i;
        }
        i++;
    }
    return -1;
}

void semtts_wait(int id){
    ttsLock(semMutexCount[id]);
    semList[id]--;
    //printf("Waiting %d %d\n", id, semList[id]);
    if(semList[id]<0){
        ttsUnlock(semMutexCount[id]);
        ttsLock(semMutexQueue[id]);
    }
    ttsUnlock(semMutexCount[id]);
}

void semtts_post(int id){
    ttsLock(semMutexCount[id]);
    semList[id]++;
    //printf("Post %d %d\n", id, semList[id]);
    if(semList[id]<=0){
        ttsUnlock(semMutexQueue[id]);
    }
    else
        ttsUnlock(semMutexCount[id]);
}

void semtts_destroy(int id){
    semList[id]=0;
    exist[id]=0;
    ttsdestroy(semMutexQueue[id]);
    ttsdestroy(semMutexCount[id]);
    semMutexQueue[id]=0;
    semMutexCount[id]=0;
}