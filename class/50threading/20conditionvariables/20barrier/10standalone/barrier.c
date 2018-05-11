/*
  barrier_nocheck.c

  Sets up a barrier blocking n threads.
  If more than n arrive, the rest can go through.
  Doesn't check for errors.
 */

#include <pthread.h>
#include <stdio.h>

static pthread_cond_t bcond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
static int count = 0;  // How many to go

// Initialize the barrier to be size n
void init_barrier(int n) {
    pthread_mutex_lock(&bmutex);
    count = n;
    fprintf(stderr, "count initialized to: %d\n", count);
    pthread_mutex_unlock(&bmutex);
}

// Wait at the barrier until all threads arrive
void wait_barrier(void) {
    pthread_mutex_lock(&bmutex); // Safely, access the barrier value
    --count;  // We're in!
    fprintf(stderr, "count decremented to: %d\n", count);
    // Anyone left? Then release lock and wait.
    while (count) pthread_cond_wait(&bcond, &bmutex); 
    pthread_cond_broadcast(&bcond); // We're good!  Wake up!
    pthread_mutex_unlock(&bmutex); // And we're done with the lock.
} 
