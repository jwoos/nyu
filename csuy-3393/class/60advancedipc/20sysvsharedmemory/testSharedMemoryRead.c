/*
  testSharedMemoryRead
  Accesses a shared memory segment reading from it.

  Sterling
 */

#include <stdlib.h>   // atoi
#include <stdio.h>    // printf
#include <ctype.h>    // isdigit
#include <sys/shm.h>  // shm...

#define MEM_SIZE 1024
#define SHM_FLAGS 0     // Since we are only accessing, we don't specify any.

int main(int argc, char* argv[]) {

    int id;  // Value to pass to shmat.  Represents id of shared memory segment.

    if (argc == 1) {
	fprintf(stderr, "Usage: testSharedMemoryRead (id | keyfile)\n");
	exit(1);
    }
    
    if (isdigit(argv[1][1])) {
        // The user handed us the shared memory segment id produced by
        // a call to shmget that created a segment.
        id = atoi(argv[1]);  // I should switch to using strtol
    } else {
        // The user handed us a file name to use with ftok to produce a key
        // that we can used to retrieve the shared memory id.
	key_t key = ftok(argv[1], 17); // pathname and "project id"
        // Getting id of previously generated shared memory segment.
	id = shmget(key, MEM_SIZE,  SHM_FLAGS);
    }
    // This is the id we will use.
    printf("id: %d\n", id);

    // Attach the shared memory.
    // Not choosing a virtual address or specifying any special flags

    int* p = (int*)shmat(id, NULL, 0);
    // Strangely, that's what the Open Group spec says and yes, if
    // there is an error, this is indeed what is returned. :-(
    if (p == (int*)-1) {  
        perror("shmat failed");
        exit(1);
    }

    printf("shared memory address: %p\n", (void*)p);

    // See what's there
    for (int i = 0; i < 10; ++i) {
        printf("p[%d] = %d\n", i, p[i]);
    }

    // We're done using it.  This doesn't prevent anyone else from
    // using it later on.
    shmdt(p);

}

