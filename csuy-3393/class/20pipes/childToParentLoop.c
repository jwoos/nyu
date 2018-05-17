/*
  Child talks to parent who listens...
  No error checking
 */

#include <string.h>  // strlen
#include <unistd.h>  // fork, pipe

const int MAXLINE = 80;

int main() {
    char line[MAXLINE];
    char mesg[] = "Listen to me!\n";
    int fd[2];

    pipe(fd);
    
    if (fork() == 0) { // Child
        write(fd[1], mesg, strlen(mesg));
    } else { // Assuming no errors... Parent listens.
        int count;
        while ((count = read(fd[0], line, MAXLINE)) > 0) {
            write(STDOUT_FILENO, line, count);
        }
    }
}
