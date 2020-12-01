#include<stdio.h>

#define EXIST 1

int semList[2048];
int semMutexQueue[2048];
int semMutexCount[2048];
int exist[2048];

extern int semtts_init(int n){
    int i = 0;
    while (i<2048){
        printf("%d\n", i);
        if (exist[i]==0){
            exist[i]=EXIST;
            semList[i] = n;
            semMutexQueue[i] = ttsmutex_init();
            semMutexCount[i] = ttsmutex_init();
            return i;
        }
        i++;
    }
    return -1;
}

extern void semtts_wait(int indMutex){
    ttsLock(semMutexCount[indMutex]);
    semList[indMutex]--;
    if(semList[indMutex]<0){
        ttsUnlock(semMutexCount[indMutex]);
        ttsLock(semMutexQueue[indMutex]);
    }
    ttsUnlock(semMutexCount[indMutex]);
}

extern void semtts_post(int indMutex){
    ttsLock(semMutexCount[indMutex]);
    semList[indMutex]++;
    if(semList[indMutex]<=0){
        ttsUnlock(semMutexQueue[indMutex]);
    }
    else{
        ttsUnlock(semMutexCount[indMutex]);
    }
}

extern void semtts_destroy(int indMutex){
    printf("mutex bien destroy\n");
    semList[indMutex]=0;
    exist[indMutex]=0;
    ttsdestroy(semMutexQueue[indMutex]);
    ttsdestroy(semMutexCount[indMutex]);
    semMutexQueue[indMutex]=0;
    semMutexCount[indMutex]=0;
}