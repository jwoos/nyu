/*
  whoIsLocking
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;

    int fd = open("something", O_RDWR);
    if (fd < 0) perror("Couldn't open something");

    pid_t pid;
    if ((pid = fcntl(fd, F_GETLK, &lock)) < 0) perror("Could not access lock");
    if (lock.l_type == F_UNLCK)
        printf("No process has the lock\n");
    else
        printf("Process %d has the lock\n", lock.l_pid);
}

