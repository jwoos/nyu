#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


extern char** environ;


// keep track of process command, args, and env
typedef struct Process {
	char* command;
	char** args;
	char** env;
} Process;

void usage(char*);

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


void usage(char* msg) {
	printf("%s\n", msg);
	printf("Usage: ./env [-i] [NAME=VALUE]... [COMMAND [ARG]...]\n");
	printf("-i: start with an empty environment\n");
	exit(EXIT_FAILURE);
}

Process* processConstruct(int argc, char** argv) {

}

void processDeconstruct(Process* proc) {
	int index;

	index = 0;
	while (proc -> args[index]) {
		free(proc -> args[index]);
		index++;
	}
	free(proc -> args);

	index = 0;
	while (proc -> env[index]) {
		free(proc -> env[index]);
	}
}
