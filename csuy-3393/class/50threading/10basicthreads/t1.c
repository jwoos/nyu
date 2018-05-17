/*
   File: t1.c
   Calling a function from a thread
*/

#include <pthread.h> 	// pthread_t, pthread_create
#include <stdio.h>   	// printf
#include <unistd.h>     // getpid

void* someFunc(void* unused) {
    fprintf(stderr, "Hi from someFunc.\n");
    return NULL;
}

int main() {
    printf("About to call someFunc\n");

    pthread_t tid; // thread id
    pthread_create(&tid, NULL, someFunc, NULL);

    printf("Back from calling someFunc\n");
    printf("main out\n");
}
