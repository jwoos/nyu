/*
  siglongjmp.c
  -jbs

  Demonstrates how sigsetjmp / siglongjmp work.

  If at least one command line argument, then restore signal mask at
  time of sigsetjmp.

  If no command line argument, then use signal mask in effect at time
  of jump.
 */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

sigjmp_buf buf;

void print_mask(sigset_t set) ;
void curly();
void larry();
void moe();

int main(int argc, char *argv[]) {
    int savesigs = 0;
    // Any arguments? Then we will save / restore the initial set of
    // blocked signals.
    if (argc > 1) savesigs = 1;

    sigset_t alarm_set;
    sigemptyset(&alarm_set);        // Initialize
    sigaddset(&alarm_set, SIGALRM); // Set sigalrm
    // Adds sigalrm to the blocked set
    sigprocmask(SIG_BLOCK, &alarm_set, NULL); 
    printf("alarm proc mask: ");
    print_mask(alarm_set);

    int val = sigsetjmp(buf, savesigs);
    if (val) {
        printf("Wow! back from a long jump! val = %d\n", val);
        sigset_t finalset;
        sigprocmask(SIG_BLOCK, NULL, &finalset); // What are they now?
        printf("final mask: ");
        print_mask(finalset);
    }
    else {
        printf("Established jump buffer\n");
        moe();
    }
}

void print_mask(sigset_t set) {
    printf("%lx\n", *(long int*)&set);
}

void moe() {
    printf("In moe\n");
    larry();
}

void larry() { 
    printf("In larry\n");
    curly();
}

void curly() { 
    printf("In curly\n");
    sigset_t signalset;
    sigemptyset(&signalset);
    sigaddset(&signalset, SIGSEGV);
    // Forget what we had set before, now it is just sigsegv.
    sigprocmask(SIG_SETMASK, &signalset, NULL);

    // Just want to check that it happened
    sigset_t signalset2;
    sigprocmask(SIG_SETMASK, NULL, &signalset2);
    printf("setting mask: ");
    print_mask(signalset2);

    siglongjmp(buf, 17);
}


