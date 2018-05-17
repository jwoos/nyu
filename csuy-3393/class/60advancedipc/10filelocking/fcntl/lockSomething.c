#include <unistd.h>
#include <fcntl.h>   // fcntl, struct flock, F_WRLCK
#include <stdio.h>   // printf, perror
#include <stdlib.h>  // exit
#include <errno.h>   // errno, EACCES, EAGAIN

int main() {
    printf("I am %d\n", getpid());

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;

    int fd = open("something", O_RDWR);

    if (fcntl(fd, F_SETLK, &lock) < 0) {
        // Does not block.
        // Returns -1 if the lock is already held and sets errno to
        // EAGAIN or EACCES
        if (errno == EAGAIN || errno == EACCES) {
            fcntl(fd, F_GETLK, &lock);
            if (lock.l_type == F_UNLCK) {
                // why we would ever get here?  After we checked the
                // lock and found it in use, it was released before we
                // asked who had it.
                printf("No process has the lock\n");
            } else {
                printf("Process %d has the lock for now\n", lock.l_pid);
            }
            fcntl(fd, F_SETLKW, &lock); // blocking request.
        }
        else {
            perror("Could not acquire lock");
        }
    }

    printf("We (process %d) have acquired the lock\n", getpid());

    pause();
}

