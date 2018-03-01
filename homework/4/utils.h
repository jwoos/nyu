#ifndef SHELL_UTILS_H
#define SHELL_UTILS_H


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define SHELL_BUFFER_SIZE 256
#define SHELL_TOKEN_SIZE 2

#define PERROR_MEMORY "Error allocating memory"
#define PERROR_SIGNAL "Error registering signal handler"
#define PERROR_WRITE "Error writing"


void perrorQuit(char*);

char* readStdin(void);


#endif
