/*
  sem_wait.c
  -jbs

  Assuming someone else has created the semaphore, does a down on it.
*/

#include <semaphore.h>  // sem_open, sem_wait
#include <stdio.h>      // printf
#include <unistd.h>     // getpid

int main() {
    sem_unlink("my_sem");
}
