/*
  filelockingcycle.c
  Demonstrate the behavior of a cycle of locks

  When a deadlock could occur, one of the processes that would
  deadlock receives an error for fcntl and an errno of EDEADLK.
 */

#include <fcntl.h>   // fcntl, struct flock, F_WRLCK
#include <stdio.h>   // fprintf, perror
#include <stdlib.h>  // exit
#include <errno.h>   // errno, EACCES, EAGAIN
#include <unistd.h>  // sleep

int main() {

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;

    int fd = open("something", O_RDWR);
    if (fd < 0) perror("Couldn't open something");

    if (fork() == 0) { // child

        lock.l_start = 0;
        lock.l_len = 5;
        fcntl(fd, F_SETLKW, &lock);
        fprintf(stderr, "Child [%d] locked bytes 0-4.\n", getpid());

        sleep(5);
        lock.l_start = 5;
        lock.l_len = 5;
        fprintf(stderr, "Child [%d] attempting to lock bytes 5-9.\n", getpid());
        if (fcntl(fd, F_SETLKW, &lock) == 0) {
            fprintf(stderr, "Child [%d] locked bytes 5-9.\n", getpid());
        }
        else {
            perror("Child failed to lock bytes 5-9.");
            fprintf(stderr, "Child terminating\n");
        }
    }
    else { // parent

        lock.l_start = 5;
        lock.l_len = 5;
        fcntl(fd, F_SETLKW, &lock);
        fprintf(stderr, "Parent [%d] locked bytes 5-9.\n", getpid());

        sleep(2);
        lock.l_start = 0;
        lock.l_len = 5;
        fprintf(stderr, "Parent [%d] attempting to lock bytes 0-4.\n", getpid());
        if (fcntl(fd, F_SETLKW, &lock) == 0) {
            fprintf(stderr, "Parent [%d] locked bytes 0-4.\n", getpid());
        }
        else {
            perror("Parent failed to lock bytes 0-4.");
            fprintf(stderr, "Parent terminating\n");
        }
    }

}
