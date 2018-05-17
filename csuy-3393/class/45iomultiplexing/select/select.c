/*
  select.c
  Test select by creating two pipes.
  Have one child write to the two pipes
  and a second child read from them.
 */

#include <stdlib.h>      // exit
#include <stdio.h>       // fprintf, perror, puts
#include <unistd.h>      // pipe, fork, read, write, close
#include <sys/select.h>  // select, FD_ZERO, FD_SET, FD_ISSET
#include <sys/wait.h>    // wait

#define READ_SIZE 10
#define TIMEOUT_SECS 10

int main(int argc, char* argv[]) {
    const int BUF_SIZE = 81;
    char buffer[BUF_SIZE];

    int pipe_fd1[2];
    if (pipe(pipe_fd1) < 0) perror("Creation of first pipe failed!");
    int pipe_fd2[2];
    if (pipe(pipe_fd2) < 0) perror("Creation of second pipe failed!");

    if (fork() == 0) {
        // first child

        fprintf(stderr, "Writing pipe one\n");
        write(pipe_fd1[1], "Twas Brillig and the slithy Toves", 34);

        fprintf(stderr, "Writing pipe two\n");
        write(pipe_fd2[1], "Did gyre and gymble in the Wabe", 31);

        exit(0);
    }

    if (fork() == 0) {
        // second child

        // Set up the file descriptor "set"
        fd_set set;
        FD_ZERO(&set);
   
        int max_fd = pipe_fd2[1] + 1;
        int fd;
        struct timeval timeout;
        //timeout.tv_sec = TIMEOUT_SECS;
        //timeout.tv_usec = 0;

        while (1) {
            // Set up for select
            timeout.tv_sec = TIMEOUT_SECS;
            timeout.tv_usec = 0;
            FD_SET(pipe_fd1[0], &set);
            FD_SET(pipe_fd2[0], &set);

            fd = select(max_fd, &set, NULL, NULL, &timeout);

            if (fd < 0) {
                perror("Select failed");
                exit(1);
            }
            if (fd == 0) {
                fprintf(stderr, "Timeout\n");
                exit(2);
            }
            char child_buf[80];
            if (FD_ISSET(pipe_fd1[0], &set)) {
                int n = read(pipe_fd1[0], child_buf, READ_SIZE);
                child_buf[n] = '\0';
                puts(child_buf);
            }
            if (FD_ISSET(pipe_fd2[0], &set)) {
                int n = read(pipe_fd2[0], child_buf, READ_SIZE);
                child_buf[n] = '\0';
                puts(child_buf);
            }
        }
        exit(0);
    }

    // Parent
    close(pipe_fd1[0]);
    close(pipe_fd2[0]);
    close(pipe_fd1[1]);
    close(pipe_fd2[1]);
    wait(NULL);
    wait(NULL);
    puts("Parent done");
}
