#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


extern char** environ;


// keep track of process command, args, and env
typedef struct Process {
	char* command;
	char** args;
	char** env;
	bool print;
} Process;

void printUsage(char*);

// find length of null terminated array
int arrLength(char**);

// return a cstring for a given value
char* findEnv(char**, char*);

Process* processConstruct(int, char**);

void processDeconstruct(Process*);


int main(int argc, char** argv) {
	// first element is the name of the current program
	Process* proc = processConstruct(argc - 1, argv + 1);

	if (proc -> print) {
		char** env = proc -> env;
		int index = 0;

		while (env[index] != NULL) {
			printf("%s\n", env[index]);
			index++;
		}
	} else {
		/* replace environ with our version of the env since exec
		 * has no variant that takes both env and considers the path
		 */
		environ = proc -> env;
		// the GNU env command doesn't fork but exec's on the process itself
		execvp(proc -> command, proc -> args);

		// if it got here that means that it failed for some reason
		perror("execve failed");
		return EXIT_FAILURE;
	}

	processDeconstruct(proc);

	return EXIT_SUCCESS;
}


void printUsage(char* msg) {
	printf("%s\n", msg);
	printf("Usage: ./env [-i] [NAME=VALUE]... [COMMAND [ARG]...]\n");
	printf("-i: start with an empty environment\n");
}

int arrLength(char** arr) {
	int length = 0;

	while ((arr[length])) {
		length++;
	}

	return length;
}

char* findEnv(char** env, char* key) {
	int index = 0;
	int length;
	char* val = NULL;

	while (env[index] != NULL) {
		length = strlen(key);
		if (strncmp(env[index], key, length) && env[index][length] == '=') {
			val = env[index];
			break;
		}
		index++;
	}

	return val;
}

Process* processConstruct(int argc, char** argv) {
	int replace = false;
	int index = 0;

	// 0 when strings are equal
	if (argc && !strncmp(argv[index], "-i", 2)) {
		replace = true;
		index++;
	}

	// get beginning env index and length of env vars
	int envIndex = -1;
	int envLength = 0;
	if (argv[index] && strchr(argv[index], '=')) {
		envIndex = index;
		index++;
		envLength++;

		while (argv[index] && strchr(argv[index], '=')) {
			index++;
			envLength++;
		}
	}

	// get beginning arg index and length of args
	int commandIndex = -1;
	int argLength = 0;
	if (argv[index]) {
		commandIndex = index;
		argLength++;

		while (argv[index]) {
			index++;
			argLength++;
		}
	}

	Process* proc = malloc(sizeof(*proc));
	if (!proc) {
		fprintf(stderr, "Error allocating memory\n");
	}
	/* Just point to the address locations of the argv, there's no need
	 * to manually copy everything out since the lifespan of argv will
	 * be the whole program since it's a variable in main. This idea
	 * also applies to the env values as well as the arguments.
	 */
	proc -> command = argv[commandIndex];

	if (commandIndex != -1) {
		proc -> args = calloc(argLength + 1, sizeof(char*));
		if (!proc -> args) {
			fprintf(stderr, "Error allocating memory\n");
		}

		for (int i = 0; i < argLength; i++) {
			proc -> args[i] = (argv + commandIndex)[i];
		}
	} else {
		proc -> print = true;
	}

	if (replace) {
		proc -> env = calloc(envLength + 1, sizeof(char*));
		if (!proc -> env) {
			fprintf(stderr, "Error allocating memory\n");
		}

		for (int i = 0; i < envLength; i++) {
			proc -> env[i] = (argv + envIndex)[i];
		}
	} else {
		int environLength = arrLength(environ);
		proc -> env = calloc(environLength + envLength + 1, sizeof(char*));
		if (!proc -> env) {
			fprintf(stderr, "Error allocating memory\n");
		}

		for (int i = 0; i < environLength; i++) {
			proc -> env[i] = environ[i];
		}

		for (int i = 0; i < envLength; i++) {
			proc -> env[i + environLength] = (argv + envIndex)[i];
		}
	}

	return proc;
}

void processDeconstruct(Process* proc) {
	free(proc -> args);
	free(proc -> env);
	free(proc);
}
