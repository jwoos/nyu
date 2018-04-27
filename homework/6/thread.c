#include "thread.h"


Thread* threadConstruct(pthread_t id) {
	Thread* thread = malloc(sizeof(*thread));
	if (thread == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

void threadDeconstruct(Thread* thread) {
	free(thread);
}
