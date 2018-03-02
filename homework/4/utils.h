#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define SHELL_BUFFER_SIZE 64
#define SHELL_TOKEN_SIZE 2

#define PERROR_MEMORY "Error allocating memory"
#define PERROR_SIGNAL "Error registering signal handler"
#define PERROR_WRITE "Error writing"
#define PERROR_FORK "Error forking"
#define PERROR_EXEC "Error execing"
#define PERROR_CHDIR "Error changing directory"
#define PERROR_OPEN "Error opening"
#define PERROR_DUP "Error duplicating fd"
#define PERROR_CLOSE "Error closing"


void perrorQuit(char*, bool);

void errorQuit(char*, bool);

void flush(void);

char* readStdin(void);


#endif
