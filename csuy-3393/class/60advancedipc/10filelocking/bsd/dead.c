/*
  dead.c
  Demonstrates that flock will allow you to deadlock

  Here we deadlock ourselves by attempting to acquire an exclusive
  lock on a single file using two different file descriptors.
 */
#include <sys/file.h>

int main() {
    int fd1 = open("a.txt", O_CREAT, 0666);
    int fd2 = open("a.txt", O_CREAT, 0666);
    flock(fd1, LOCK_EX);
    flock(fd2, LOCK_EX);
}
