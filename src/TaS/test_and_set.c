#include<stdio.h>

#define EXIST 1

int mutexList[2048];
int exist[2048];


int mutex_init(void){
    int i = 0;
    while (i<2048){
        if (exist[i]==0){
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
        /*: "=r" (lock)   // output operand
        : "r"(1)        //do we need input operand?
        : "%eax")*/       // clobbered register %eax
}

void unlock(int indMutex){
    __asm__ (   
            "movl $0, %%eax\n"
            "xchgl %%eax, %0\n"
            :
            :"m" (mutexList[indMutex])
            :"eax"
        );
        /*: "=r" (lock)   // output operand
        : "r"(0)        //do we need input operand?
        : "%eax")*/       // clobbered register %eax
}

void destroy(int indMutex){
    printf("mutex bien destroy\n");
    mutexList[indMutex]=0;
    exist[indMutex]=0;
}