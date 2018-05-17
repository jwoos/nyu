/*
  pipeTest.c
  Child talking to parent
  Note that we did not "bother" closing anything.
  Could prove problematic in general.
 */

#include <string.h>  // strlen
#include <unistd.h>  // fork, pipe
#include <stdio.h>   // perror
#include <stdlib.h>  // exit
#include <sys/types.h>  // pid_t

const int MAXLINE = 80;

int main() {
    char line[MAXLINE];
    char mesg[] = "Listen to me!\n";  // Buffer to print
    int fd[2]; // pipe's file descriptors
    pid_t pid; // fork's return

    // Create the pipe and make sure it worked.
    if (pipe(fd) < 0) {
        perror("Could not open pipe");
        exit(1);
    }
    
    if ((pid = fork()) == 0) {        // Child
        // writes to the parent
        write(fd[1], mesg, strlen(mesg));
    } else if (pid > 0) {             // Parent
        // read from the child
        int count = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line,  count);  // display to the screen.
    } else {
        perror("Fork failed");
        exit(2);
    }
}
