/*
   File: t3.c
   Calling a function
   and giving it a chance to run.

   Demonstrates how exiting the main thread as opposed to letting main
   implicitly call exit, allows other threads to complete.

*/

#include <pthread.h> 	// pthread_t, pthread_create
#include <stdio.h>   	// printf

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

    pthread_exit(0);
}
