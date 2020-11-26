#include<stdio.h>

void lock(void){
    asm (   "movl $1, %eax"
            "movl %eax, (lock))"
            "testl %eax, %eax"
            "jnz enter"
            "ret"
        : "=r" (lock)   // output operand
        : "r"(1)        //do we need input operand?
        : "%eax")       // clobbered register %eax
}

void unlock(void){
    asm (   "movl $0, %eax"
            "movl %eax, (lock))"
            "ret"
        : "=r" (lock)   // output operand
        : "r"(0)        //do we need input operand?
        : "%eax")       // clobbered register %eax
}