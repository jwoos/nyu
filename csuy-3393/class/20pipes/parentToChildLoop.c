/*
  Parent talks to child who listens... (???)
  What happens when we run this?
 */

#include <string.h>  // strlen
#include <unistd.h>  // fork, pipe

const int MAXLINE = 80;

int main() {
    char line[MAXLINE];
    char mesg[] = "Listen to me!\n";
    int fd[2];

    pipe(fd);
    
    if (fork() > 0) { // Parent
        write(fd[1], mesg, strlen(mesg));
    } else { // Assuming no errors... Child listens.
        close(fd[1]);
        int count;
        while ((count = read(fd[0], line, MAXLINE)) > 0) {
            write(STDOUT_FILENO, line, count);
        }
    }
}
