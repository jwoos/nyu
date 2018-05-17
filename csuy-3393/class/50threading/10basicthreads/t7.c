/*
   File: t7.c
   Yield between "reading" the value and modifying it.
   What reasons might this not mess up the count?
*/

#include <pthread.h> 	// pthread_t, pthread_create
#include <stdio.h>	// printf
#include <unistd.h>	// sleep

#define MAX 20
int x = 0;

void* someFunc(void* unused) {
  fprintf(stderr, "Hi from someFunc\n");
  for (int i = 0; i < MAX; ++i) {
    x++;
    fprintf(stderr, ".");
    sleep(1);
  }
  fprintf(stderr, "Bye from someFunc\n");
  return NULL;
}
void* anotherFunc(void* unused) {
  fprintf(stderr, "Hi from anotherFunc\n");
  for (int i = 0; i < MAX; ++i) {
    int tmp = x;
    fprintf(stderr, "o");
    sleep(1);
    x = --tmp;
  }
  fprintf(stderr, "Bye from anotherFunc\n");
  return NULL;
}

int main() {
  pthread_t tid1, tid2; // thread id
  printf("About to create threads\n");
  pthread_create(&tid1, NULL, someFunc, NULL);
  pthread_create(&tid2, NULL, anotherFunc, NULL);
  printf("Back from creating threads\n");
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  printf("x = %d\n", x);
  printf("main out\n");
}
