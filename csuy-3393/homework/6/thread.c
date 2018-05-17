#include "thread.h"


Thread* threadConstruct(pthread_t id) {
	Thread* thread = malloc(sizeof(*thread));
	if (thread == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	thread -> id = id;

	thread -> name = NULL;

	return thread;
}

void threadDeconstruct(void* thread) {
	Thread* t = (Thread*)thread;
	free(t -> name);
	free(t);
}

void threadSetName(Thread* thread, char* name) {
	int nameLength = strlen(name) + 1;
	thread -> name = malloc(sizeof(char) * nameLength);
	if (thread -> name == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strncpy(thread -> name, name, nameLength);
}
