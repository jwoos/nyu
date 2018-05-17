// procon.c
// Producer Consumer Problem
// from Tanenbaum's MOS3e, fig 2-32.

#include <stdio.h>
#include <pthread.h>
#define MAX 100

pthread_mutex_t the_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condc = PTHREAD_COND_INITIALIZER;
pthread_cond_t condp = PTHREAD_COND_INITIALIZER;

int buffer = 0;
void *consumer(void* ptr);
void *producer(void* ptr);

// Create one producer and one consumer. 
// Join the producer and consumer threads before finishing.
int main() {
    pthread_t pro, con;
    pthread_create(&pro, NULL, producer, NULL);
    pthread_create(&con, NULL, consumer, NULL);
    pthread_join(pro, NULL);
    pthread_join(con, NULL);
}

// Producer function
//   Ignores the parameter and returns NULL (actually 0)
//   Loops MAX times waiting for the buffer to be "empty",
//   i.e. zero and then stores a non-zero int value there.
void *producer(void* ptr) {
    for (int i = 1; i <= MAX; i++) {
        pthread_mutex_lock(&the_mutex);
        while (buffer != 0) {
            pthread_cond_wait(&condp, &the_mutex);
        }
        buffer = i;
        fprintf(stderr, "Producer producing: %d.  Buffer full.\n", i);
        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

// Consumer function
//   Ignores the parameter and returns NULL (actually 0) Loops MAX
//   times waiting for the buffer to be "not empty", i.e. non-zero and
//   then consumes the value, leaving zero in its place.
void *consumer(void* ptr) {
    for (int i = 1; i <= MAX; i++) {
        pthread_mutex_lock(&the_mutex);
        while (buffer == 0) {
            pthread_cond_wait(&condc, &the_mutex);
        }
        fprintf(stderr, "Consumer consuming %d.  Buffer free.\n", buffer);
        buffer = 0;
        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

