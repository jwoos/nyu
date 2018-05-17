// sharedMemCreate.c

#include <sys/mman.h> // shm_open, mmap, PROT_READ, PROT_WRITE, MAP_SHARED
#include <fcntl.h>    // O_CREAT, O_RDWR, S_IRUSR, S_IWUSR
#include <unistd.h>   // ftruncate
#include <stdio.h>    // printf
#include <string.h>   // strcpy

int main() {
    int fd = shm_open("/mymem", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    printf("fd: %d\n", fd);
    //ftruncate(fd, 0);
    ftruncate(fd, 1024);
    char *addr = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    strcpy(addr, "the cat in the hat");
    printf("%s\n", addr);
    munmap(addr, 0);
}
