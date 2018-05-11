/*
  nonblocking-for-file.c
  John Sterling

  Setting O_NONBLOCK on a regular file.

  Yes, you can set it but it doesn't have any effect.

  The code below sets O_NONBLOCK for a file on open
  (and then checks that O_NONBLOCK really was set).

  Then reads the file tracking the number of reads that blocked.
  There won't be any.

  Does the same thing with fcntl.  Same effect.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h> // strcpy
#include <unistd.h>
#include <fcntl.h>  // fcntl, O_RDONLY
#include <errno.h>

int main(int argc, char* argv[]) {
    const int BUF_SIZE = 81;
    char filename[BUF_SIZE];
    char buffer[BUF_SIZE];

    if (argc == 1) strcpy(filename, "jabberwocky");
    else strcpy(filename, argv[1]);

    // Demonstrating that while you "can set" O_NONBLOCK on a regular file
    // it does not have any effect
    int fd = open(filename, O_RDONLY | O_NONBLOCK);
    if (fd < 0) perror("Failed to open with O_NONBLOCK");
    int flags = fcntl(fd, F_GETFL);
    if ((flags & O_NONBLOCK) == O_NONBLOCK)
        puts("Successfully enabled nonblock from open");
    else
        puts("Failed to enable nonblock from open");
    puts("");

    // n will be used for the return value of read, i.e. number of
    // characters read in a single call to read or -1 if an "error".
    // Attempting to read from a stream that is set to O_NONBLOCK but
    // would require blocking to get any data should result in an
    // error with errno set to EAGAIN.
    int n;

    int blocked_count = 0;
    while ((n = read(fd, buffer, BUF_SIZE-1)) != 0) {
        if (n < 0) {
            if (errno == EAGAIN) ++blocked_count;
            // Should have to block at some point but doesn't.
            perror("We had some read error on the file."); 
        }
        buffer[n] = '\0';
        puts(buffer);
    }
    fprintf(stderr, "%d reads would have resulted in blocking\n\n", blocked_count);
  
    int fd2 = open(filename, O_RDONLY);
    int flags2 = fcntl(fd2, F_GETFL);
    flags2 |= O_NONBLOCK;
    fcntl(fd2, F_SETFL, flags2);
    flags2 = fcntl(fd, F_GETFL);
    if ((flags2 & O_NONBLOCK) == O_NONBLOCK)  // ==  higher precedence than &
        puts("Successfully enabled nonblock from fcntl");
    else
        puts("Failed to enable nonblock from fcntl");
    puts("");

    blocked_count = 0;
    while ((n = read(fd2, buffer, BUF_SIZE-1)) != 0) {
        if (n < 0) {
            // Should have to block at some point but doesn't.
            if (errno == EAGAIN) ++blocked_count;
            perror("Read failed after fcntl O_NONBLOCK.");
        }
        buffer[n] = '\0';
        puts(buffer);
    }
    fprintf(stderr, "%d reads would have resulted in blocking\n\n",
            blocked_count);
}
