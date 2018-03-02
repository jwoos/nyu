#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "shell.h"
#include "utils.h"
#include "token.h"


extern int PID;
extern int status;


int main(void) {
	handleSignals();

	char* input;
	Token* token;

	while (true) {
		prompt();

		// read input a character at a time
		input = readStdin();

		if (input[0] == '\0') {
			free(input);
			input = NULL;
			break;
		} else if (input[0] == '\n' || input[0] == ' ') {
			free(input);
			input = NULL;
			continue;
		}

		token = tokenConstruct(input);
		free(input);
		input = NULL;

		// builtins
		bool cont = builtins(token);
		if (cont) {
			continue;
		}

		// Expand variables, or just $? in this case
		tokenExpand(token);

		PID = fork();
		if (PID < 0) {
			perrorQuit(PERROR_FORK);
		}

		if (PID == 0) {
			// do any redirections necessary
			tokenRedirect(token);

			// child process
			if (execvp((token -> tokens + token -> index)[0], token -> tokens + token -> index) < 0) {
				perrorQuit(PERROR_EXEC);
			}
		} else {
			// parent process
			wait(&status);
			PID = 0;
		}

		// clean up
		tokenDeconstruct(token);
		token = NULL;
	}

	return EXIT_SUCCESS;
}
