#include "utils.h"


void perrorQuit(char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

char* readStdin(void) {
	uint32_t size = SHELL_BUFFER_SIZE;
	uint32_t position = 0;

	char* buffer = calloc(size, sizeof(char));
	if (!buffer) {
		perrorQuit(PERROR_MEMORY);
	}

	int c;

	while (1) {
		c = getchar();

		// EOF or newline
		if (c == -1 || c == '\n') {
			// handle line breaks
			if (buffer[position - 1] != '\\') {
				buffer[position] = '\0';
				break;
			} else {
				position--;
				continue;
			}
		}

		buffer[position] = c;
		position++;

		if (position >= size) {
			size += SHELL_BUFFER_SIZE;

			buffer = realloc(buffer, size);
			if (!buffer) {
				perrorQuit(PERROR_MEMORY);
			}
		}
	}

	return buffer;
}
