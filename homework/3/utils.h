#ifndef _DU_UTILS_H
#define _DU_UTILS_H


#include <unistd.h>


void printUsage(char*);

void perrorQuit(char*);

int ftwHandler(const char*, const struct stat*, int, struct FTW*);

#endif
