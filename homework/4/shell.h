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


int inputCheck(char*);

int builtins(Token*);

void prompt(void);

void sigintHandler(int);

void handleSignals(void);

void runProcess(Token*);


#endif
