#include<stdio.h>

#define EXIST 1

int mutexList[2048];
int exist[2048];


int mutex_init(void){
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
void lock(int indMutex){
    __asm__ (   
            "enter: movl $1, %%eax\n"
            "xchgl %%eax, %0\n"
            "testl %%eax, %%eax\n"
            "jnz enter\n"
            :
            :"m" (mutexList[indMutex])
            :"eax"
        );
}

void unlock(int indMutex){
    __asm__ (   
            "movl $0, %%eax\n"
            "xchgl %%eax, %0\n"
            :
            :"m" (mutexList[indMutex])
            :"eax"
        );
}

void destroy(int indMutex){
    printf("mutex bien destroy\n");
    mutexList[indMutex]=0;
    exist[indMutex]=0;
}