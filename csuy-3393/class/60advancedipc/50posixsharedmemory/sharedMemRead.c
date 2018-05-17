// sharedMemRead.c
// -jbs

#include <sys/mman.h> // shm_open, mmap, PROT_READ, MAP_SHARED
#include <fcntl.h>    // O_RDONLY
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>  // ftruncate
#include <string.h>  // strcpy

int main() {

    int fd = shm_open("/mymem", O_RDONLY, S_IRUSR | S_IWUSR);
    printf("fd: %d\n", fd);
    //ftruncate(fd, 1024);
    char *addr = mmap(NULL, 1024, PROT_READ, MAP_SHARED, fd, 0);
    close(fd);
    printf("%s\n", addr);
    munmap(addr, 0);
}
