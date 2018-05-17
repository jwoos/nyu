/*
  Free the Shared Memory
  Sterling
 */

#include <stdlib.h>  // atoi
#include <stdio.h>   // printf
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/shm.h> // shmget, shmctl, ftok, key_t, IPC_RMID

int main(int argc, char* argv[]) {
    int id;
    if (argc == 1) {
        fprintf(stderr, "Usage: testSharedMemoryFree (id | keyfile)\n");
        exit(EXIT_FAILURE);
    }
    if (isdigit(argv[1][1])) id = atoi(argv[1]);
    else {
	key_t key = ftok(argv[1], 17); // pathname and "project id"
        id = shmget(key, 1024, 0666);
    }
    printf("id: %d\n", id);

    shmctl(id, IPC_RMID, NULL);
}
