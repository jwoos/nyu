/*
   sleep defined as in Steven's APUE

   General idea:
   - Remember all settings before you change things.
   - Set up a "do nothing" signal handler for SIGALRM using sigaction
   - To handle race
     - Before calling alarm, use sigprocmask to set up a signal mask
       that blocks SIGALRM
     - Call alarm (with SIGALRM blocked) then sigsuspend yourself,
       enabling SIGALRM
   - When you wake up, SIGALRM will be automatically blocked again.
   - Put everything back the way your found it and return the number
     of "unslept" seconds.
*/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static void sig_alrm(int signo)
{
    /* nothing to do, just returning wakes up sigsuspend() */
}

unsigned int sleep(unsigned int nsecs) {

    struct sigaction newact, oldact;
    sigset_t newmask, oldmask, suspmask;
    unsigned int unslept;

    /* set our handler, save previous information */
    newact.sa_handler = sig_alrm;  // sig_alrm is our handlerr
    sigemptyset(&newact.sa_mask);  // Not blocking on any additoinal signals
    newact.sa_flags = 0;           // No flags
    sigaction(SIGALRM, &newact, &oldact);

    // Before we set our alarm, we want to be sure to be blocking on SIGALRM
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGALRM);
    // SIG_BLOCK adds our newmask to the signals being blocked
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);

    // Set the alarm.
    alarm(nsecs);
    suspmask = oldmask;
    sigdelset(&suspmask, SIGALRM); /* make sure SIGALRM isn't blocked */
    sigsuspend(&suspmask); /* wait for any signal to be caught */
 
    // some signal has been caught, SIGALRM is now blocked due to sigprocmask 
    unslept = alarm(0);
    sigaction(SIGALRM, &oldact, NULL); /* reset previous action */

    // reset signal mask, which unblocks SIGALRM
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    return(unslept);
}
