#include <stdio.h>


int PID;
char* prompt;


void initializePrompt(void) {
	prompt = getenv("PS1");

	if (prompt == NULL) {
		prompt = "$ ";
	}
}

void prompt(void) {
	printf("%s ", getenv())
}

void sigactionHandler(int sig) {
	switch (sig) {
		case SIGINT: {
			if (PID > 0) {
				kill(PID, SIGINT);
				PID = 0;
			} else {
				flush();
				prompt();
			}
			break;
		}

		default: {
			break;
		}
	}
}

void handleSignals(void) {
	struct sigaction act;

	act.sa_handler = &sigactionHandler;
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, NULL) < 0) {
		perror("error registering signal handler");
		exit(EXIT_FAILURE);
	}
}
