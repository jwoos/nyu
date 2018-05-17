/*
  sigdemo1.c
  jbs

  Catches SIGINT
  loop 100 times, printing "Hanging out"
  purpose is to demonstrate effect of 
 */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

typedef void (*sig_handler_t)(int num);

void myHandler(int signalNum) {
    puts("Ouch!!  Stop that!!!");
}

int main() {
    // Set handler for SIGINT, and remember the prior disposition
    sig_handler_t old_handler = signal(SIGINT, myHandler);

    // Hang out
    for (int i = 0; i < 100; ++i) {
        puts("Hanging out");
        sleep(1);
    }

    // Restoring original dislosition for SIGINT
    signal(SIGINT, old_handler);
}
