#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "shell.h"


extern int PID;


int main(int argc, char** argv) {
	handleSignals();

	char* input;

	while (true) {
		prompt();

	}
}
