#ifndef CHAT_UTILS_H
#define CHAT_UTILS_H


#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


void println(char*, ...);

void handleError(int, char*, bool);

void handlePerror(int, char*, bool);

int max(int, int);

int min(int, int);


#endif
