#include "shell.h"


extern int PID;
extern int status;


void prompt(void) {
	char* prompt = getenv("PS1");

	if (prompt == NULL) {
		prompt = "$ ";
	}

	printf("%s", prompt);
}

void sigintHandler(int sig) {
	if (PID > 0) {
		kill(PID, sig);
		PID = 0;
		flush();
		wait(&status);
	} else {
		flush();
	}
}

void handleSignals(void) {
	struct sigaction act;

	act.sa_handler = &sigintHandler;
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, NULL) < 0) {
		perrorQuit(PERROR_SIGNAL);
	}
}
