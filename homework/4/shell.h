#ifndef SHELL_SHELL_H
#define SHELL_SHELL_H


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "utils.h"


int PID;


void prompt(void);

void sigactionHandler(int);

void handleSignals(void);


#endif
