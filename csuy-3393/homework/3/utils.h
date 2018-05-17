#ifndef DU_UTIL_H
#define DU_UTIL_H


#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_CAPACITY 16

#define PERROR_MEMORY "Error allocating memory"
#define PERROR_DIRECTORY_OPEN "Error opening directory"
#define PERROR_DIRECTORY_READ "Error reading directory"
#define PERROR_DIRECTORY_CLOSE "Error closing directory"
#define PERROR_STAT "Error calling stat"


enum Resize {
	ADD,
	MULTIPLY,
	SUBTRACT,
	DIVIDE,
	SET
};


void printUsage(char*);

void perrorQuit(char*);

int min(int, int);

int max(int, int);

char* join(char*, char*, char);


#endif
