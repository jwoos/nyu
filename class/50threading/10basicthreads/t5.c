/*
  File: t5.c
  Add a second thread decrementing the same thing.  
  Spit out a different char.  
  Observe the scheduling.
*/

#include <pthread.h> 	// pthread_t, pthread_create
#include <stdio.h>	// printf

#define MAX 20
int x = 0;

void* someFunc(void* unused) {
  fprintf(stderr, "Hi from someFunc\n");
  for (int i = 0; i < MAX; ++i) {
    x++;
    fprintf(stderr, ".");
  }
  fprintf(stderr, "Bye from someFunc\n");
  return NULL;
}

void* anotherFunc(void* unused) {
  fprintf(stderr, "Hi from anotherFunc\n");
  for (int i = 0; i < MAX; ++i) {
    x--;
    fprintf(stderr, "o");
  }
  fprintf(stderr, "Bye from anotherFunc\n");
  return NULL;
}

int main() {
  pthread_t tid1, tid2; // thread id
  printf("About to call someFunc\n");
  pthread_create(&tid1, NULL, someFunc, NULL);
  pthread_create(&tid2, NULL, anotherFunc, NULL);
  printf("Back from calling someFunc\n");
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  printf("x = %d\n", x);
  printf("main out\n");
}
