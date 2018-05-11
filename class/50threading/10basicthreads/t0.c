/*
   File: t0.c
   Calling a function.
*/

#include <stdio.h>

void* someFunc(void* unused) {
    fprintf(stderr, "Hi from someFunc.\n");
    return NULL;
}

int main() {
    printf("About to call someFunc.\n");

    someFunc(NULL);

    printf("Back from calling someFunc\n");
    printf("main out\n");
}
