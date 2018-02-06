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
} Process;

void printUsage(char*);

// find length of null terminated array
int arrLength(char**);

Process* processConstruct(int, char**);

void processDeconstruct(Process*);


int main(int argc, char** argv) {
	// first element is the name of the current program
	Process* proc = processConstruct(argc - 1, argv + 1);

	// the GNU env command doesn't fork but exec's on the process itself
	execvpe(proc -> command, proc -> args, proc -> env);

	perror("execvpe failed");

	/* this is technically never reached as the process is replaced by the above program
	 * the cleanup is done as if the process had terminated i.e. all memory
	 * on heap will be freed
	 */
	processDeconstruct(proc);

	// if it got here that means that it failed for some reason
	return EXIT_FAILURE;
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

Process* processConstruct(int argc, char** argv) {
	if (!argc) {
		printUsage("A command must be present");
		exit(EXIT_FAILURE);
	}

	int replace = false;
	int index = 0;

	// 0 when strings are equal
	if (!strcmp(argv[index], "-i")) {
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
	/* Just point to the address locations of the argv, there's no need
	 * to manually copy everything out since the lifespan of argv will
	 * be the whole program since it's a variable in main. This idea
	 * also applies to the env values as well as the arguments.
	 */
	proc -> command = argv[commandIndex];

	if (commandIndex != -1) {
		proc -> args = calloc(argLength + 1, sizeof(char*));

		for (int i = 0; i < argLength; i++) {
			proc -> args[i] = (argv + commandIndex)[i];
		}
	} else {
		printUsage("A command must be present");
		exit(EXIT_FAILURE);
	}

	if (replace) {
		proc -> env = calloc(envLength + 1, sizeof(char*));

		for (int i = 0; i < envLength; i++) {
			proc -> env[i] = (argv + envIndex)[i];
		}
	} else {
		if (envIndex != -1) {
			int environLength = arrLength(environ);
			proc -> env = calloc(environLength + envLength + 1, sizeof(char*));

			for (int i = 0; i < environLength; i++) {
				proc -> env[i] = environ[i];
			}

			for (int i = 0; i < envLength; i++) {
				proc -> env[i + environLength] = (argv + envIndex)[i];
			}
		} else {
			// passing in no env variables is a valid command - just use environ
			proc -> env = environ;
		}
	}

	return proc;
}

void processDeconstruct(Process* proc) {
	free(proc -> args);
	free(proc -> env);
	free(proc);
}
