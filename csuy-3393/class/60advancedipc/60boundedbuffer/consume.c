/*
  consume.c
  -jbs

  remove items with safe_remove_bb
 */

#include <sys/mman.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "bb.h"

int safe_remove_bb(BB *bb, sem_t *mut, sem_t *full, sem_t *empty) {
    // there must be some slots that are full otherwise we have
    // nothing to remove
    sem_wait(full);  

    // Now we know that removing will be successful and we just have
    // to get ownership of the data
    sem_wait(mut);
    int result = remove_bb(bb, NULL);
    sem_post(mut);
    
    // Increment the number of slots available to fill
    sem_post(empty);

    return result;
}

int main(int argc, char* argv[]) {

    // this initialization code should be shared between produce and
    // consume...

    // Set up the three semaphores to lock the bounded buffer
    sem_t* mut = sem_open("mutex", 0);

    // Track the number of slots that are full. Consumer will wait on
    // this. Producer will post it.
    sem_t* full = sem_open("full", 0);

    // Track the number of slots that are empty. Producer will wait on
    // this. Consumer will post it.
    sem_t* empty = sem_open("empty", 0);

    // Set up shared memory for bounded buffer
    int fd = shm_open("/bb", O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(fd, sizeof(BB));
    BB *bb = mmap(NULL, sizeof(BB), PROT_READ | PROT_WRITE, 
                      MAP_SHARED, fd, 0);
    close(fd);

    int val = safe_remove_bb(bb, mut, full, empty);
    printf("removed: %d\n", val);

    print_bb(bb);

    munmap(bb, 0);
}
