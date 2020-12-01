#include<stdio.h>

#define EXIST 1

int mutexList[2048];
int exist[2048];


extern int ttsmutex_init(void){
    int i = 0;
    while (i<2048){
        printf("%d\n", i);
        if (exist[i]==0){
            exist[i]=EXIST;
            printf("init : %d\n", i);
            return i;
        }
        i++;
    }
    return -1;
}

extern void ttsLock(int indMutex){
    int flag = 1;
    while (flag == 1){
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

extern void ttsUnlock(int indMutex){
    __asm__ (   
            "movl $0, %%eax\n"
            "xchgl %%eax, %0\n"
            :
            :"m" (mutexList[indMutex])
            :"eax"
        );
}

extern void ttsdestroy(int indMutex){
    printf("mutex bien destroy\n");
    mutexList[indMutex]==0;
    exist[indMutex]==0;
}