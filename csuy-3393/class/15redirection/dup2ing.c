/*
  dup2ing.c
  demonstrates redirection of standard input by
  1) opening a file.
  2) dup2-ing the original fd to 0

  Note that error checking was omitted for readability.
  You should provide it!
 */

#include <unistd.h> // close
#include <fcntl.h>  // open
#include <stdlib.h> // exit

const int BUFFSIZE = 100;

int main() {
    int	fd ;
    char line[BUFFSIZE];

    // read from the console and print to the console
    // (same as in redirect.c)
    int n = read(0, line, BUFFSIZE-1);
    line[n] = '\n';
    write(1, line, n+1);

    // Open the file before redirecting
    // (same as in duping.c)
    fd = open("/etc/passwd", O_RDONLY);

    // redirect standard input to come from the file
    dup2(fd, 0);  // Now there's no ambiguity as to which fd to use as
                  // the target

    // and close the file's original descriptor as we don't want
    // unused open file descriptors.
    // (same as in duping.c)
    close(fd);

    // again read from standard input, now the file,
    // and print to the console. Same code as in the beginning.
    // (and same as in redirect.c)
    n = read(0, line, BUFFSIZE-1);
    line[n] = '\n';
    write(1, line, n+1);
}
