/*
  createPipe.c
  Create a pipe, write and read.
  jbs

  No error checking, for clarity.
 */

#include <string.h>  // strlen
#include <unistd.h>  // pipe

const int MAXLINE = 80;

int main() {
    char mesg[] = "Listen to me!\n";  // string to write
    char line[MAXLINE];               // buffer to read into
    int fd[2];                        // file descriptors for pipe

    pipe(fd);                         // Create the pipe
    
    write(fd[1], mesg, strlen(mesg)); // Send the message to the pipe
    int count = read(fd[0], line, MAXLINE);  // Read it back

    // Display the read msg to standard ouput
    write(STDOUT_FILENO, line,  count);
}
