/*
  sem_post.c
  -jbs

  Assuming someone else has created the semaphore, does an up on it.
*/
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    sem_t* my_sem = sem_open("my_sem", 0);

    printf("pid %d: calling sem_post\n", getpid());
    sem_post(my_sem);
    printf("pid %d: completed sem_post\n", getpid());
}
