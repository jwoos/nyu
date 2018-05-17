/*
  duping.c
  demonstrates redirection of standard input by
  1) opening a file.
  2) closing file descriptor 0
  3) duping the original fd

  Note that error checking was omitted for readability.
  You should provide it!
 */

#include <unistd.h> // close
#include <fcntl.h>  // open
#include <stdlib.h> // exit

const int BUFFSIZE = 100;

int main() {
    char line[BUFFSIZE];

    // read from the console and print to the console
    // (same as in redirect.c)
    int n = read(0, line, BUFFSIZE-1);
    line[n] = '\n';
    write(1, line, n+1);

    // Open the file before redirecting
    int fd = open("/etc/passwd", O_RDONLY);

    // redirect standard input to come from the file
    close(0);   // first closing standard input
    dup(fd);    // and then dup'ing the file descriptor into the
                // lowest free fd. Returns new fd or -1.

    // and close the file's original descriptor as we don't want
    // unused open file descriptors.
    close(fd);

    // again read from standard input, now the file,
    // and print to the console. Same code as in the beginning.
    // (and same as in redirect.c)
    n = read(0, line, BUFFSIZE-1);
    line[n] = '\n';
    write(1, line, n+1);
}
