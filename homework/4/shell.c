#include "shell.h"


extern int PID;
extern int status;


/* -1 for break
 * 0 for nothing
 * 1 for continue
 */
int inputCheck(char* input) {
	int act = 0;

	if (input[0] == '\0') {
		free(input);

		act = -1;
	} else if (input[0] == '\n' || input[0] == ' ') {
		free(input);

		act = 1;
	}

	return act;
}

/* -1 for break
 * 0 for nothing
 * 1 for continue
 */
int builtins(Token* token) {
	int act = 0;
	/* Built ins
	 * If one of these matches, don't bother exec'ing
	 */
	if (!strncmp(token -> tokens[0], "exit", 4)) {
		tokenDeconstruct(token);
		token = NULL;

		act = -1;
	} else if (!strncmp(token -> tokens[0], "cd", 2)) {
		if (chdir(token -> tokens[1])) {
			perrorQuit(PERROR_CHDIR, false);
		}

		tokenDeconstruct(token);

		token = NULL;

		act = 1;
	}

	return act;
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
		perrorQuit(PERROR_SIGNAL, true);
	}
}

void runProcess(Token* token) {
	PID = fork();
	if (PID < 0) {
		perrorQuit(PERROR_FORK, false);
	}

	if (PID == 0) {
		// do any redirections necessary
		tokenRedirect(token);

		// child process
		if (execvp((token -> tokens + token -> index)[0], token -> tokens + token -> index) < 0) {
			perrorQuit(PERROR_EXEC, true);
		}
	} else {
		// parent process
		wait(&status);
		PID = 0;
	}
}
