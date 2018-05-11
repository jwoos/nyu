/*
   File: t4.c
   Add a global variable that the thread will increment in a loop.  
   Spit out a char to stderr at the same time.  
   Main will display the result.
*/

#include <pthread.h> 	// pthread_t, pthread_create
#include <stdio.h>	// printf

#define MAX 20
int x = 0;

void* someFunc(void* unused) {
    printf("Hi from someFunc\n");
    for (int i = 0; i < MAX; ++i) {
        x++;
        fprintf(stderr, ".");
    }
    printf("Bye from someFunc\n");
    return NULL;
}

int main() {
    printf("About to call someFunc\n");

    pthread_t tid; // thread id
    pthread_create(&tid, NULL, someFunc, NULL);
    printf("Back from calling someFunc\n");

    pthread_join(tid, NULL);
    printf("x = %d\n", x);

    printf("main out\n");
}
