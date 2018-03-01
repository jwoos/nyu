#include "token.h"


Token* constructToken(char* input) {
	Token* tokenStruct = malloc(sizeof(*tokenStruct));

	uint32_t size = SHELL_TOKEN_SIZE;
	char** tokens = malloc(sizeof(char*) * size);
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
		token = strtok(NULL, " ");
		if (token == NULL) {
			break;
		}

		if (index == size) {
			size += SHELL_TOKEN_SIZE;
			tokens = realloc(tokens, sizeof(char*) * size);
			if (tokens == NULL) {
				perrorQuit(PERROR_MEMORY);
			}
		}

		tokenLength = strlen(token);
		tokens[index] = malloc(sizeof(char) * tokenLength + 1);
		if (tokens[index] == NULL) {
			perrorQuit(PERROR_MEMORY);
		}

		strncpy(tokens[index], token, tokenLength + 1);

		index++;
	}

	tokenStruct -> capacity = size;
	tokenStruct -> size = index;
	tokenStruct -> tokens = tokens;

	return tokenStruct;
}

void deconstructToken(Token* token) {
	for (uint32_t i = 0; i < token -> size; i++) {
		free(token -> tokens[i]);
	}
	free(token -> tokens);
	free(token);
}
