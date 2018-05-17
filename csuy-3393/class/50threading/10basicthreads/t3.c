/*
   File: t3.c
   Add pthread_join(pid, NULL) before the "so long" from main.  
   Now the thread's outputs should be seen.
*/

#include <pthread.h> 	// pthread_t, pthread_create
#include <stdio.h>	// printf
#include <unistd.h>	// getpid

void* someFunc(void* unused) {
    printf("Hi from someFunc. ");
    return NULL;
}

int main() {
    printf("About to call someFunc\n");

    pthread_t tid; // thread id
    pthread_create(&tid, NULL, someFunc, NULL);

    printf("Back from calling someFunc\n");

    pthread_join(tid, NULL);

    printf("main out\n");
}
