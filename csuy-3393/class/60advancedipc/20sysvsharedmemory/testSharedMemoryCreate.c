/*
  testSharedMemory
  Sets up a shared memory segment and writes to it.

  Sterling
 */

#include <stdlib.h>   // atoi
#include <stdio.h>    // printf
#include <sys/shm.h>  // shmget, shmat, shmdt, ftok, IPC_PRIVATE, IPC_CREAT

int main(int argc, char* argv[]) {
    int id;
    if (argc == 1) {
        // If no command line arguments then let the system figure out an id
        id = shmget(IPC_PRIVATE, 1024, 0666 | IPC_CREAT);
        //printf("id: %d\n", id);  // Others can use this id
    } else {
        // If we pass a file name, use that to generate a key
        // Note that the pathname must represent an existing file
        key_t key = ftok(argv[1], 17); // pathname and "project id"
        if (key < 0) {
            perror("ftok failed");
            exit(1);
        }
        id = shmget(key, 1024, 0666 | IPC_CREAT);
    }
    printf("id: %d\n", id);  // Others can use this id
    

    if (id < 0) perror("shmget failed");

    // Attach the shared memory.
    // Not specifying a virtual address or any special flags
    int* p = (int*)shmat(id, NULL, 0);
    if (p == (int*)-1) {
        perror("shmat failed");
        exit(1);
    }

    printf("shared memory address: %p\n", (void*)p);

    // Write something to the shared memory
    for (int i = 0; i < 10; ++i) {
        p[i] = i * i;
    }

    // We're done using it.  This doesn't prevent anyone else from
    // using it later on.
    shmdt(p);

}
