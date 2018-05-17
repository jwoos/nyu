/*
  flock.c
  Simplified version of LPI's t_flock 
  (mostly just stripped of error checking, but also not using his header)
 */

#include <sys/file.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    int fd, lock;
    const char *lname;
    time_t now;

    lock = (argv[2][0] == 's') ? LOCK_SH : LOCK_EX; 
    if (argv[2][1] == 'n')
        lock |= LOCK_NB;
    fd = open(argv[1], O_RDONLY); /* Open file to be locked */ 

    lname = (lock & LOCK_SH) ? "LOCK_SH" : "LOCK_EX";

    
    now = time(NULL);
    printf("PID %ld: requesting %s at %s\n", (long) getpid(), lname, ctime(&now));
    if (flock(fd, lock) == -1) {
        if (errno == EWOULDBLOCK) {
            printf("PID %ld: already locked - bye!\n", (long) getpid()); 
            exit(1);
        }
        else {
            printf("flock (PID=%ld)", (long) getpid());
            exit(0);
        }
    }
    now = time(NULL);
    printf("PID %ld: granted %s at %s\n", (long) getpid(), lname, ctime(&now));
    sleep((argc > 3) ? atoi(argv[3]) : 10);
    now = time(NULL);
    printf("PID %ld: releasing %s at %s\n", (long) getpid(), lname, ctime(&now));
           flock(fd, LOCK_UN);
    exit(EXIT_SUCCESS);
}
