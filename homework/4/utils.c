#include "utils.h"


void perrorQuit(char* msg, bool quit) {
	perror(msg);
	if (quit) {
		exit(EXIT_FAILURE);
	}
}

void errorQuit(char* msg, bool quit) {
	fprintf(stderr, "%s\n", msg);
	if (quit) {
		exit(EXIT_FAILURE);
	}
}

void flush(void) {
	if (write(STDOUT_FILENO, "\n", 1) < 0) {
		perrorQuit(PERROR_WRITE, true);
	}
}

char* readStdin(void) {
	uint32_t size = SHELL_BUFFER_SIZE;
	uint32_t position = 0;

	char* buffer = calloc(size, sizeof(char));
	if (!buffer) {
		perrorQuit(PERROR_MEMORY, true);
	}

	int c;

	while (1) {
		if (position >= size) {
			size += SHELL_BUFFER_SIZE;

			buffer = realloc(buffer, size);
			if (!buffer) {
				perrorQuit(PERROR_MEMORY, true);
			}
		}

		c = getchar();

		// EOF or newline
		bool isEOF = c == EOF && feof(stdin);
		bool error = c == EOF;
		bool isNewline = c == '\n';

		if (position == 0 && isEOF) {
			// actual EOF (c-d)
			flush();
			exit(EXIT_SUCCESS);
			break;
		} else if (position == 0 && isNewline) {
			// newline when empty doesn't count
			buffer[position] = c;
			break;
		} else if (isNewline) {
			// actual newline - we should process it now
			break;
		} else if (error) {
			/* error is set when EOF or just error getting char
			 * such as when it's interrupted by a signal.
			 * Since we already caught EOF we can just say that the signal
			 * interrupted. This will do nothing as the driver will
			 * ignore all input starting with space
			 */
			buffer[position] = ' ';
			break;
		}

		buffer[position] = c;
		position++;
	}

	return buffer;
}
