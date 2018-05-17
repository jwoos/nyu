/*
  produce3.c
  -jbs

  add items with safe_add_bb
 */

#include <sys/mman.h>  // shm_open, mmap
#include <semaphore.h> // sem_t, sem_wait
#include <stdio.h>     // printf, perror
#include <stdlib.h>    // exit, atoi
#include <unistd.h>    // ftruncate, close
#include <stdbool.h>   // bool, true, false
#include "bb.h"

void safe_add_bb(BB *bb, int val, sem_t *mut, sem_t *full, sem_t *empty);
void init_posix_sem_and_shm(sem_t **mut, sem_t **full, sem_t **empty, BB **bb);

// Takes int values to add from the command line.
int main(int argc, char* argv[]) {

    // Set up three semaphores
    sem_t* mut;   // To lock the bounded buffer
    sem_t* full;  // Track the number of slots that are full. 
    sem_t* empty; // Track the number of slots that are empty.
    BB *bb;       // The bounded buffer

    init_posix_sem_and_shm(&mut, &full, &empty, &bb);

    // add whatever values were provided on the command line
    for (int i = 1; i < argc; ++i) {
        // shouldn't use atoi but being lazy.
        safe_add_bb(bb, atoi(argv[i]), mut, full, empty);
    }

    munmap(bb, 0);
}

// safe_add_bb: wrap the call to add_db with thread_safe protection
void safe_add_bb(BB *bb, int val, sem_t *mut, sem_t *full, sem_t *empty) {
    sem_wait(empty);  // wait for there to be an empty slot
    sem_wait(mut);    // secure the bounded buffer
    // We know we will be successful so we are passing NULL for the
    // success parameter.
    add_bb(bb, val, NULL); 
    sem_post(mut);    // release the bounded buffer
    sem_post(full);   // let the world know there is another full slot
}

void init_posix_sem_and_shm(sem_t **mut, sem_t **full, sem_t **empty, BB **bb) {
    // Set up three semaphores
    // To lock the bounded buffer
    *mut = sem_open("mutex", 0);

    // Track the number of slots that are full. Consumer will wait on
    // this. Producer will post it.
    *full = sem_open("full", 0);

    // Track the number of slots that are empty. Producer will wait on
    // this. Consumer will post it.
    *empty = sem_open("empty", 0);

    // Set up shared memory for bounded buffer
    int fd = shm_open("/bb", O_RDWR, S_IRUSR | S_IWUSR);
    printf("fd: %d\n", fd);
    ftruncate(fd, sizeof(BB));
    
    *bb = (BB*)mmap(NULL, sizeof(BB), PROT_READ | PROT_WRITE, 
               MAP_SHARED, fd, 0);
    close(fd);

}
