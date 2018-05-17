/*
  sem_wait.c
  -jbs

  Assuming someone else has created the semaphore, does a down on it.
*/

#include <semaphore.h>  // sem_open, sem_wait
#include <stdio.h>      // printf
#include <unistd.h>     // getpid

int main() {
    sem_t* my_sem = sem_open("my_sem", 0);

    printf("pid %d: calling sem_wait\n", getpid());
    sem_wait(my_sem);
    printf("pid %d: completed sem_wait\n", getpid());
}
