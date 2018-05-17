/*
  createSemaphore.c
  -jbs

  Along with other files in this directory demonstrates basic use of
  posix semaphores.
*/
#include <semaphore.h>
#include <stdio.h>


int main() {

    sem_open("my_sem", O_CREAT, 0666, 2);

}
