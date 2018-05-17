/*
  Display the bounded buffer
  -jbs
 */

#include <sys/mman.h>   // shm_open, mmap, ...
#include <semaphore.h>  // sem_t, sem_open, SEM_FAILED, ...
#include <stdio.h>      // perror, printf
#include <stdlib.h>     // exit
#include <unistd.h>     // ftruncate, close
#include <stdbool.h>
#include "bb.h"

int main(int argc, char* argv[]) {

    // Set up three semaphores
    // To lock the bounded buffer
    sem_t* mut = sem_open("mutex", 0);
    if (mut == SEM_FAILED) {
        perror("mutex");
        exit(1);
    }

    // Set up shared memory for bounded buffer
    int fd = shm_open("/bb", O_RDWR, S_IRUSR | S_IWUSR);
    printf("fd: %d\n", fd);
    ftruncate(fd, sizeof(BB));
    BB *bb = mmap(NULL, sizeof(BB), PROT_READ | PROT_WRITE, 
                      MAP_SHARED, fd, 0);
    close(fd);

    sem_wait(mut);
    print_bb(bb);
    sem_post(mut);

    munmap(bb, 0);
}
