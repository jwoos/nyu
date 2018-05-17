/*
  setUp.c
  -jbs

  Creates the shared memory and semaphores for a bounded buffer that
 */

#include <sys/mman.h>  // shm_open, mmap, munmap, PROT_READ, PROT_WRITE, MAP_SHARED
#include <semaphore.h> // sem_t, sem_open, O_CREAT, O_EXCL, SEM_FAILED
#include <stdio.h>     // perror, printf
#include <stdlib.h>    // exit
#include <unistd.h>    // ftruncate, close
#include <stdbool.h>   // bool, true, false
#include "bb.h"        // BB, init_bb

int main() {

    // Set up three semaphores
    // To lock the bounded buffer
    sem_t* mut = sem_open("mutex", O_CREAT | O_EXCL, 0666, 1);
    if (mut == SEM_FAILED) {
        perror("mutex");
        exit(1);
    }

    // Track the number of slots that are full. Consumer will wait on
    // this. Producer will post it.
    sem_t* full = sem_open("full", O_CREAT | O_EXCL, 0666, 0);
    if (mut == SEM_FAILED) {
        perror("mutex");
        exit(1);
    }

    // Track the number of slots that are empty. Producer will wait on
    // this. Consumer will post it.
    sem_t* empty = sem_open("empty", O_CREAT | O_EXCL, 0666, BUF_SIZE);
    if (mut == SEM_FAILED) {
        perror("mutex");
        exit(1);
    }

    // Set up shared memory for bounded buffer
    int fd = shm_open("/bb", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    printf("fd: %d\n", fd);
    ftruncate(fd, sizeof(BB));
    BB *bb = mmap(NULL, sizeof(BB), PROT_READ | PROT_WRITE, 
                      MAP_SHARED, fd, 0);
    close(fd);
    init_bb(bb);

    munmap(bb, 0);
}
