#ifndef SHELL_TOKEN_H
#define SHELL_TOKEN_H


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"


typedef struct Token {
	char** tokens;
	uint32_t size;
	uint32_t capacity;
} Token;


Token* tokenConstruct(char*);

void tokenDeconstruct(Token*);

// expand variables
void tokenExpand(Token*);


#endif
