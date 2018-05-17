/*
   File: t1b.c
   Calling a function from a thread

   Same as t1 but prints the process id both in main and in the thread
   function, someFunc.  Why?  Someone wondered if the Linux
   implementation used different process ids for threads within a
   single process.  This test shows that they have the same process
   id. Thank goodness!
*/

#include <pthread.h> 	// pthread_t, pthread_create
#include <stdio.h>   	// printf
#include <unistd.h>     // getpid

void* someFunc(void* unused) {
    fprintf(stderr, "Hi from someFunc. pid: %d\n", getpid());
    return NULL;
}

int main() {
    printf("About to call someFunc.  pid: %d\n", getpid());

    pthread_t tid; // thread id
    pthread_create(&tid, NULL, someFunc, NULL);

    printf("Back from calling someFunc\n");
    printf("main out\n");
}
