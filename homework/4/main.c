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

		input = readStdin();

		if (input[0] == '\0') {
			free(input);
			break;
		} else if (input[0] == '\n' || input[0] == ' ') {
			flush();
			free(input);
			continue;
		}

		token = tokenConstruct(input);
		free(input);
		input = NULL;

		if (!strncmp(token -> tokens[0], "exit", 4)) {
			tokenDeconstruct(token);
			token = NULL;

			exit(EXIT_SUCCESS);
		} else if (!strncmp(token -> tokens[0], "cd", 2)) {
			if (chdir(token -> tokens[1])) {
				perrorQuit(PERROR_CHDIR);
			}

			tokenDeconstruct(token);
			token = NULL;

			continue;
		}

		tokenExpand(token);

		PID = fork();
		if (PID < 0) {
			perrorQuit(PERROR_FORK);
		}

		if (PID == 0) {
			if (execvp(token -> tokens[0], token -> tokens) < 0) {
				perrorQuit(PERROR_EXEC);
			}
		} else {
			wait(&status);
			PID = 0;
		}

		tokenDeconstruct(token);
		token = NULL;
	}

	return EXIT_SUCCESS;
}
