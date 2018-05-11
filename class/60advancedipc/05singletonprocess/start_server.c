/*
  start_server.c
  simple (simplistic) approach to using files for synchronization.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void handle(int ignore) {}

int main() {
    signal(SIGINT, handle);

    int fd = open("unique.txt", O_CREAT | O_EXCL, 0666);
    if (fd == -1) {
        if (errno == EEXIST) {
            fprintf(stderr, "Server exists, bailing\n");
        } else {
            perror("failed to open file unique.txt");
        }
        exit(1);
    }

    fprintf(stderr, "server starting\n");
    pause();

    fprintf(stderr, "server shutting down\n");
    close(fd);
    unlink("unique.txt");

}
