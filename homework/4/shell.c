#include "shell.h"


extern int PID;
extern int status;


bool builtins(Token* token) {
	/* Built ins
	 * If one of these matches, don't bother exec'ing
	 */
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

		return true;
	}

	return false;
}

/* show prompt
 * if PS1 is set, use that. otherwise
 * just use $
 */
void prompt(void) {
	char* prompt = getenv("PS1");

	if (prompt == NULL) {
		prompt = "$ ";
	}

	printf("%s", prompt);
}

// handle sigint
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

// register handler
void handleSignals(void) {
	struct sigaction act;

	act.sa_handler = &sigintHandler;
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, NULL) < 0) {
		perrorQuit(PERROR_SIGNAL);
	}
}
