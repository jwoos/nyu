#ifndef SHELL_SHELL_H
#define SHELL_SHELL_H


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "utils.h"
#include "token.h"


int PID;
int status;


bool builtins(Token*);

void prompt(void);

void sigintHandler(int);

void handleSignals(void);


#endif
