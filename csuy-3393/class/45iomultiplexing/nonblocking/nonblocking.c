/*
    Demo of O_NONBLOCK

    O_NONBLOCK is intended only for descriptors that could block
    forever, such as sockets, not for regular files.

    Demonstrating use of O_NONBLOCK on a pipe.
 */

#include <stdlib.h> // exit
#include <stdio.h>  // printf, puts, perror
#include <unistd.h> // read, write, pipe, 
#include <fcntl.h>  // fcntl, F_GETFL, F_SETFL, O_NONBLOCK
#include <errno.h>  // errno, EAGAIN
#include <string.h> // strlen
#include <signal.h> // signal, SIGINT, SIGQUIT

// Global so that it can be accessed by signal handler.
int pipe_fd[2];

void handler(int signum) {
    char msg[] = "Handler writing to pipe";
    int msg_len = strlen(msg);
    if (write(pipe_fd[1], msg, msg_len) != msg_len) {
        fprintf(stderr, "handler write to pipe_fd wrong length\n");
    }
}

int main(int argc, char* argv[]) {
    const int BUF_SIZE = 81; // seems like a nice number
    char buffer[BUF_SIZE];

    /* We will use the signals to give us a way to write something to
       the pipe while blocked attempting to read.
       The user should be able to enter either ^C or ^  \
    */
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);

    // Create the pipe. We will read from it and the interrupt handler
    // will write to it.
    fprintf(stderr, "Creating the pipe\n");
    if (pipe(pipe_fd) < 0) {
        perror("Failed to create the pipe.\n");
        exit(1);
    }

    // Showing that reading from an empty pipe normally blocks
    // Blocks till we send something into the pipe (Try ^C or ^\)
    fprintf(stderr, "About to read from the pipe\n");
    int n; // Number of chars that get read 
    while ((n = read(pipe_fd[0], buffer, BUF_SIZE-1)) == -1)
        if  (errno == EINTR) continue;
    //    fprintf(stderr, "Read %d bytes\n", n); // debugging
    buffer[n] = '\0';
    fprintf(stderr, "Msg: %s\n", buffer);
    puts("Passed first pipe read\n============\n");

    // Enable NONBLOCK for pipe
    //   get a copy of the file control flags
    int flags = fcntl(pipe_fd[0], F_GETFL);
    flags |= O_NONBLOCK;  // add nonblocking to the copy of the flags
    // Set the pipe's flags to include nonblock
    fcntl(pipe_fd[0], F_SETFL, flags);

    // Check NONBLOCK for pipe (did we do it right?)
    flags = fcntl(pipe_fd[0], F_GETFL);
    // if (flags & O_NONBLOCK)
    if ((flags & O_NONBLOCK) == O_NONBLOCK) // Note precedence!!!
        puts("nonblock for pipe enabled from fcntl");
    else
        puts("nonblock for pipe failed in fcntl");

    // Showing that we no longer block on reading from an empty pipe.
    fprintf(stderr, "About to read from the pipe with O_NONBLOCK\n");
    n = read(pipe_fd[0], buffer, BUF_SIZE-1);
    // What should a non-blocking read return if there's nothing there?
    if (n < 0) {
        // read returns -1 when there's nothing there.
        // If it returned zero we would not be able to distinguish from a
        // closed stream.
        perror("Failed to read pipe.");
        printf("errno: %d, EAGAIN: %d, EWOULDBLOCK: %d\n",
               errno, EAGAIN, EWOULDBLOCK);
    }
    else puts(buffer);

    // Showing that we can still read from the pipe when it has something.
    fprintf(stderr, "Writing 'hello' to pipe\n");
    write(pipe_fd[1], "hello", 6);
    n = read(pipe_fd[0], buffer, BUF_SIZE-1);
    if (n < 0) perror("Failed to read pipe after writing 'hello'.");
    else fprintf(stderr, "Read the following from the pipe: %s\n", buffer);

    // Should add in a read loop displaying number of times a read
    // failed with EAGAIN / EWOULDBLOCK. Note that it is likely to be
    // a very very big number.
}
