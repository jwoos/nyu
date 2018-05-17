// sharedMemUnlink.c
// -jbs

#include <sys/mman.h> // shm_unlink
#include <stdio.h>    // perror

int main() {
    if (shm_unlink("/mymem") == -1) {
        perror("Could not unlink /mymem");
    }
}
