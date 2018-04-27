#include "utils.h"


void println(char* fmt, ...) {
	va_list args;

	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);

	printf("\n");
}

void handleError(int status, char* msg, bool quit) {
	if (status != 0) {
		errno = status;
		perror(msg);

		if (quit) {
			exit(EXIT_FAILURE);
		}
	}
}

void handlePerror(int status, char* msg, bool quit) {
	if (status != 0) {
		perror(msg);

		if (quit) {
			exit(EXIT_FAILURE);
		}
	}
}
