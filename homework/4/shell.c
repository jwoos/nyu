#include "shell.h"


void prompt(void) {
	char* prompt = getenv("PS1");

	if (prompt == NULL) {
		prompt = "$ ";
	}

	printf("%s", prompt);
}

void flush(void) {
	if (write(STDOUT_FILENO, "\n", 1) < 0) {
		perrorQuit(PERROR_WRITE);
	}
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
		perrorQuit(PERROR_SIGNAL);
	}
}

