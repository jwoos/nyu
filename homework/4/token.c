#include "token.h"


extern int status;


// tokenize by space
Token* tokenConstruct(char* input) {
	Token* tokenStruct = malloc(sizeof(*tokenStruct));

	uint32_t size = SHELL_TOKEN_SIZE;
	char** tokens = malloc(size * sizeof(char*));
	uint32_t index = 0;
	uint32_t tokenLength = 0;

	char* token = strtok(input, " ");
	if (token != NULL) {
		tokenLength = strlen(token);

		tokens[index] = malloc(sizeof(char) * tokenLength + 1);
		if (tokens[index] == NULL) {
			perrorQuit(PERROR_MEMORY);
		}

		strncpy(tokens[index], token, tokenLength + 1);

		index++;
	}

	while (token != NULL) {
		/* increase size of array
		 * This has to come first and compared to size - 1
		 * as we need an extra space at the end to put in
		 * a null.
		 */
		if (index == size - 1) {
			size += SHELL_TOKEN_SIZE;
			tokens = realloc(tokens, sizeof(char*) * size);
			if (tokens == NULL) {
				perrorQuit(PERROR_MEMORY);
			}
		}

		token = strtok(NULL, " ");
		if (token == NULL) {
			break;
		}

		tokenLength = strlen(token);
		tokens[index] = malloc(sizeof(char) * tokenLength + 1);
		if (tokens[index] == NULL) {
			perrorQuit(PERROR_MEMORY);
		}

		strncpy(tokens[index], token, tokenLength + 1);

		index++;
	}

	tokens[index] = '\0';

	tokenStruct -> capacity = size;
	tokenStruct -> size = index;
	tokenStruct -> tokens = tokens;
	tokenStruct -> index = 0;

	return tokenStruct;
}

void tokenDeconstruct(Token* token) {
	for (uint32_t i = 0; i < token -> size; i++) {
		free(token -> tokens[i]);
	}
	free(token -> tokens);
	free(token);
}

void tokenExpand(Token* token) {
	for (uint32_t i = 0; i < token -> size; i++) {
		if (!strncmp(token -> tokens[i], "$?", 2)) {
			/* 8 bits can only be 3 characters + 1 null character
			 * -1 - 255
			 */
			char* buf = malloc(sizeof(char) * 4);
			if (buf == NULL) {
				perrorQuit(PERROR_MEMORY);
			}

			if (WIFSIGNALED(status)) {
				// if exited because of signal
				if (snprintf(buf, 4, "%d", WTERMSIG(status) + 128) < 0) {
					perrorQuit(PERROR_PRINTF);
				}
			} else {
				if (snprintf(buf, 4, "%d", WEXITSTATUS(status)) < 0) {
					perrorQuit(PERROR_PRINTF);
				}
			}
			free(token -> tokens[i]);

			token -> tokens[i] = buf;
		}
	}
}

static void _rightRedirect(char* right) {
	char* buf[2];
	uint32_t index = 0;

	uint8_t count = 0;
	for (uint32_t i = 0; i < strlen(right); i++) {
		if (right[i] == '>') {
			count++;
		}
	}

	bool append = count == 2;

	char* tok = strtok(right, ">");
	while (tok != NULL) {
		buf[index] = tok;
		index++;
		tok = strtok(NULL, ">");
	}

	int fd;
	char* filename = index > 1 ? buf[1] : buf[0];
	if (append) {
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	} else {
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	if (fd < 0) {
		perrorQuit(PERROR_OPEN);
	}

	if (index > 1) {
		// fd was provided
		if (dup2(fd, atol(buf[0])) < 0) {
			perrorQuit(PERROR_DUP);
		}
	} else {
		// fd was not provided, default to stdout
		if (dup2(fd, STDOUT_FILENO) < 0) {
			perrorQuit(PERROR_DUP);
		}
	}

	if (close(fd) < 0) {
		perrorQuit(PERROR_CLOSE);
	}
}

static void _leftRedirect(char* left) {
	char* buf = strtok(left, "<");

	int fd = open(buf, O_RDONLY);
	if (fd < 0) {
		perrorQuit(PERROR_OPEN);
	}

	if (dup2(fd, STDIN_FILENO) < 0) {
		perrorQuit(PERROR_DUP);
	}

	if (close(fd) < 0) {
		perrorQuit(PERROR_CLOSE);
	}
}

static void _cleanUp(Token* token, int32_t a, int32_t b) {
	if ((b == 0 && a == token -> size - 1) || (b == token -> size - 1 && a == 0)) {
		// redirection on either end
		token -> index = 1;
		token -> size--;
		free(token -> tokens[token -> size]);
		token -> tokens[token -> size] = NULL;
	} else if ((b == 0 && a == 1) || (a == 0 && b == 1)) {
		// all redirection at the beginning
		token -> index = 2;
	} else if ((b == token -> size - 1 && a == token -> size - 2) || (b == token -> size - 2 && a == token -> size - 1)) {
		// all redirection at the end
		for (int i = 0; i < 2; i++) {
			token -> size--;
			free(token -> tokens[token -> size]);
			token -> tokens[token -> size] = NULL;
		}
	} else if ((a == 0 && b == -1) || (a == -1 && b == 0)) {
		// single redirection at the beginning
		token -> index = 1;
	} else if ((a == token -> size - 1 && b == -1) || (a == -1 && b == token -> size -1)) {
		// single redirection at the end
		token -> size--;
		free(token -> tokens[token -> size]);
		token -> tokens[token -> size] = NULL;
	}
}

void tokenRedirect(Token* token) {
	char* current;
	int32_t rightIndex = -1;
	int32_t leftIndex = -1;

	// find the redirect tokens if there are any
	for (uint32_t i = 0; i < token -> size; i++) {
		current = token -> tokens[i];

		uint32_t j = 0;
		while (current[j] != '\0') {
			if (current[j] == '>' && rightIndex == -1) {
				rightIndex = i;
			} else if (current[j] == '<' && leftIndex == -1) {
				leftIndex = i;
			}

			j++;
		}
	}

	if (rightIndex != -1) {
		_rightRedirect(token -> tokens[rightIndex]);
	}

	if (leftIndex != -1) {
		_leftRedirect(token -> tokens[leftIndex]);
	}

	_cleanUp(token, leftIndex, rightIndex);
}
