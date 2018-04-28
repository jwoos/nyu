#include "thread.h"


Thread* threadConstruct(pthread_t id) {
	Thread* thread = malloc(sizeof(*thread));
	if (thread == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	thread -> id = id;

	return thread;
}

void threadDeconstruct(void* thread) {
	free(thread);
}
