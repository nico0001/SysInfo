#include<stdio.h>

#define EXIST 1

int mutexList[2048];
int exist[2048];

int ttsmutex_init(void){
    int i = 0;
    while (i<2048){
        if (exist[i]!=EXIST){
            exist[i]=EXIST;
            return i;
        }
        i++;
    }
    return -1;
}

void ttsLock(int indMutex){
    int flag = 1;
    while (flag == 1){
        // boucle avec le flag du cache évitant les appels atomiques
        while (mutexList[indMutex] == 1){}

        __asm__ (
            "movl $1, %%eax\n"
            "xchgl %%eax, %1\n"
            "movl %%eax, %0\n"
            :"=m" (flag)
            :"m" (mutexList[indMutex])
            :"eax"
        );
    }
}

void ttsUnlock(int indMutex){
    __asm__ (   
            "movl $0, %%eax\n"
            "xchgl %%eax, %0\n"
            :
            :"m" (mutexList[indMutex])
            :"eax"
        );
}

void ttsdestroy(int indMutex){
    printf("mutex bien destroy\n");
    mutexList[indMutex]=0;
    exist[indMutex]=0;
}