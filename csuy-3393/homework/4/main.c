#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "shell.h"
#include "utils.h"
#include "token.h"


int main(void) {
	handleSignals();

	char* input;
	Token* token;

	while (true) {
		prompt();

		// read input a character at a time
		input = readStdin();

		int inputCheckAction = inputCheck(input);
		if (inputCheckAction == -1) {
			break;
		} else if (inputCheckAction == 1) {
			continue;
		}

		token = tokenConstruct(input);
		free(input);
		input = NULL;

		// builtins
		int builtinsAction = builtins(token);
		if (builtinsAction == -1) {
			break;
		} else if (builtinsAction == 1) {
			continue;
		}

		// Expand variables, or just $? in this case
		tokenExpand(token);

		runProcess(token);

		// clean up
		tokenDeconstruct(token);
		token = NULL;
	}

	return EXIT_SUCCESS;
}
