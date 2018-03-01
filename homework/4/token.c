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
				if (snprintf(buf, 4, "%d", WTERMSIG(status) + 127) < 0) {
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
