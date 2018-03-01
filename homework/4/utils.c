#include "utils.h"


void perrorQuit(char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void flush(void) {
	if (write(STDOUT_FILENO, "\n", 1) < 0) {
		perrorQuit(PERROR_WRITE);
	}
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
		if (position >= size) {
			size += SHELL_BUFFER_SIZE;

			buffer = realloc(buffer, size);
			if (!buffer) {
				perrorQuit(PERROR_MEMORY);
			}
		}

		c = getchar();

		// EOF or newline
		bool isEOF = c == EOF && feof(stdin);
		bool error = c == EOF;
		bool isNewline = c == '\n';
		if (isEOF || isNewline || error) {
			if (position == 0 && isNewline) {
				buffer[position] = c;
			} else if (error) {
				buffer[position] = ' ';
			}

			break;
		}

		buffer[position] = c;
		position++;
	}

	return buffer;
}
