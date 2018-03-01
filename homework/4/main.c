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

		if (!strncmp(input, "exit", 4)) {
			exit(EXIT_SUCCESS);
		} else if (!strncmp(input, "cd", 2)) {
			printf("Not implemented");
			exit(EXIT_FAILURE);
		}

		if (input[0] != '\0') {
			token = tokenConstruct(input);
			free(input);
			input = NULL;

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
			}

			tokenDeconstruct(token);
			token = NULL;
		} else {
			free(input);
		}
	}

	return EXIT_SUCCESS;
}
