/* 
   File: t8.c
   Insert a mutex to protect the updating of x.
*/

#include <pthread.h> 	// pthread_t, pthread_create
#include <stdio.h>	// printf
#include <unistd.h>	// sleep

#define MAX 20
int x = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* someFunc(void* unused) {
    fprintf(stderr, "Hi from someFunc\n");
    for (int i = 0; i < MAX; ++i) {
        pthread_mutex_lock(&mutex);
        x++;
        pthread_mutex_unlock(&mutex);
        fprintf(stderr, ".");
        sleep(1);
    }
    fprintf(stderr, "Bye from anotherFunc\n");
    return NULL;
}

void* anotherFunc(void* unused) {
    fprintf(stderr, "Hi from anotherFunc\n");
    for (int i = 0; i < MAX; ++i) {
        pthread_mutex_lock(&mutex);
        int tmp = x;
        fprintf(stderr, "o");
        sleep(1);
        x = --tmp;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    fprintf(stderr, "Bye from anotherFunc\n");
    return NULL;

}

int main() {
    pthread_t tid1, tid2; // thread id
    printf("About to create threads\n");
    pthread_create(&tid1, NULL, someFunc, NULL);
    pthread_create(&tid2, NULL, anotherFunc, NULL);
    printf("Back from creating threads\n");
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("x = %d\n", x);
    printf("main out\n");
}
