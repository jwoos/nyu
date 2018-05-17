#include "utils.h"


void printUsage(char* msg) {
	printf("%s\n", msg);
	printf("Usage: ./du [FILEPATH]\n");
}

void perrorQuit(char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a > b ? a : b;
}

char* join(char* a, char* b, char delimiter) {
	char* buffer;
	int size = 0;
	int aLength = strlen(a);
	int bLength = strlen(b);
	size += aLength;
	size += bLength;
	size += 2;

	buffer = calloc(size, sizeof(char));
	if (buffer == NULL) {
		perrorQuit(PERROR_MEMORY);
	}

	int index = 0;
	strncpy(buffer, a, aLength);
	index += aLength;

	buffer[index] = delimiter;
	index++;

	strncpy(buffer + index, b, bLength);
	index += bLength;

	buffer[index] = '\0';

	return buffer;
}
