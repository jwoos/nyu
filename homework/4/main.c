#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "shell.h"
#include "utils.h"
#include "token.h"


extern int PID;


int main(int argc, char** argv) {
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
			token = constructToken(input);
			free(input);
			input = NULL;

			for (uint32_t i = 0; i < token -> size; i++) {
				printf("%s\n", token -> tokens[i]);
			}

			deconstructToken(token);
			token = NULL;

			exit(EXIT_FAILURE);
		}


		free(input);
	}
}
