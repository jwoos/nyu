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
int arrLength(void*);

Process* processConstruct(int, char**);

void processDeconstruct(Process*);


int main(int argc, char** argv) {
	// first element is the name of the current program
	Process* proc = processConstruct(argc - 1, argv + 1);

	// the GNU env command doesn't fork but exec's on the process itself
	execvpe(proc.command, proc.args, proc.env);

	/* this is technically never reached as the process is replaced by the above program
	 * the cleanup is done as if the process had terminated i.e. all memory
	 * on heap will be freed
	 */
	processDeconstruct(proc);

	return EXIT_SUCCESS;
}


void printUsage(char* msg) {
	printf("%s\n", msg);
	printf("Usage: ./env [-i] [NAME=VALUE]... [COMMAND [ARG]...]\n");
	printf("-i: start with an empty environment\n");
}

int arrLength(void* arr) {
	int length = 0;

	while (arr[length]) {
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
	int envIndex;
	int commandIndex;
	int argIndex;


	// 0 when strings are equal
	if (!strcmp(argv[index], "-i")) {
		replace = true;
		index++;
	}

	envIndex = index;
	while (strchr(argv[index], '=')) {
		index++;
	}

	commandIndex = index;
	index++;

	argIndex = index;

	Process* proc = malloc(sizeof(*proc));
	proc -> command = argv[commandIndex];

	proc -> args = calloc(argIndex - envIndex + 1, sizeof(char*));
	memcpy(proc -> args, argv[argIndex], argIndex - envIndex);

	if (replace) {
		proc -> env = calloc(commandIndex - envIndex + 1, sizeof(char*));
		memcpy(proc -> env, argv[envIndex], commandIndex - envIndex);
	} else {
		int environLength = arrLength(environ);
		proc -> env = calloc(environLength + (commandIndex - index + 1), char*);
		memcpy(proc -> env, environ, environLength);
		memcpy(proc -> env + environLength, argv[envIndex], commandIndex - envIndex);
	}

	return proc;
}

void processDeconstruct(Process* proc) {
	free(proc -> args);
	free(proc -> env);
	free(proc);
}
