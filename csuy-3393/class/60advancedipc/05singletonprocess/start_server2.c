/*
  start_server2
  -jbs

  Allows for possibility that the server died without removing the
  file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>  // memset
#include <signal.h>  // kill

void handle(int ignore) {}

int main() {
    signal(SIGINT, handle);
    //signal(SIGQUIT, handle);

    int fd = open("unique.txt", O_CREAT | O_EXCL | O_RDWR, 0666);
    if (fd == -1) {
        if (errno == EEXIST) {
            fprintf(stderr, "file unique.txt exists.\n"
                            "Hm, does server actualy exist?\n");
              // Need to be able to write if taking over
            fd = open("unique.txt", O_RDWR);
            char buf[80];
            memset(buf, 0, 80);
            read(fd, buf, 80);
            int pid = atoi(buf);
            if (kill(pid, 0) < 0) {
                fprintf(stderr, "Looks like server %d died, pid %d taking over\n", pid, getpid());
                ftruncate(fd, 0);
                FILE *fp = fdopen(fd, "w");
                fprintf(fp, "%d", getpid());
            } else {
                fprintf(stderr, "Yeah, he's alive, bailing\n");
                exit(1);
            }
        } else {
            perror("failed to open file unique.txt");
            exit(1);
        }
    }

    fprintf(stderr, "server %d starting\n", getpid());
    FILE *fp = fdopen(fd, "w");
    fprintf(fp, "%d\n", getpid());
    fclose(fp);
    pause();

    fprintf(stderr, "server %d shutting down\n", getpid());
    unlink("unique.txt");

}
