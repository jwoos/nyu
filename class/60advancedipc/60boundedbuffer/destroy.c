/*
  destroy.c
  -jbs

  Free up posix resources
 */

#include <sys/mman.h>   // shm_unlink
#include <semaphore.h>  // sem_unlink

int main() {

    // Free up the three semaphores and the shared memory
    sem_unlink("mutex");
    sem_unlink("full");
    sem_unlink("empty");
    shm_unlink("/bb");
}
