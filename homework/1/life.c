#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


#define DEFAULT_ROWS 10
#define DEFAULT_COLUMNS 10
#define DEFAULT_FILENAME "life.txt"
#define DEFAULT_GENERATIONS 10


typedef struct GameState {
	uint8_t** board;
	uint32_t columns;
	uint32_t rows;
	uint32_t generation;
	bool padding;
} GameState;


typedef struct Configuration {
	uint32_t columns;
	uint32_t rows;
	char* filename;
	uint32_t generations;
} Configuration;


Configuration* configurationInitialize(char**, int);

void configurationDeinitialize(Configuration*);

GameState* gameStateInitialize(Configuration*);

void gameStateNext(GameState*);

void gameStatePrint(GameState*, uint32_t);

void gameStateDeinitialize(GameState*);


int main(int argc, char** argv) {
	// setup
	Configuration* config = configurationInitialize(argv, argc);
	/*GameState* state = gameStateInitialize(config);*/

	printf("%s\n", config -> filename);
	/*
	 *uint32_t i = 0;
	 *do {
	 *    gameStateNext(state);
	 *    gameStatePrint(state);
	 *} while (i < config -> generations);
	 */

	// teardown
	/*gameStateDeinitialize(state);*/
	configurationDeinitialize(config);

	return EXIT_SUCCESS;
}


Configuration* configurationInitialize(char** argv, int argc) {
	Configuration* config = malloc(sizeof(*config));

	config -> generations = DEFAULT_GENERATIONS;
	config -> filename = DEFAULT_FILENAME;
	config -> columns = DEFAULT_COLUMNS;
	config -> rows = DEFAULT_ROWS;

	/* Parse arguments
	 * It'll execute everything from the first match since there
	 * are no break's. If it doesn't get set, then it'll keep its
	 * default value set above.
	 */
	switch (argc) {
		case 5:
			config -> generations = strtol(argv[4], NULL, 10);

		case 4:
			config -> filename = argv[3];

		case 3:
			config -> columns = strtol(argv[2], NULL, 10);

		case 2:
			config -> rows = strtol(argv[1], NULL, 10);
	}

	return config;
}


void configurationDeinitialize(Configuration* config) {
	free(config);
}

GameState* gameStateInitialize(Configuration* config) {
	GameState* state = malloc(sizeof(*state));
	state -> board = malloc(sizeof(int**));

	return state;
}

void gameStateDeinitialize(GameState* state) {
	for (uint32_t y = 0; y < state -> rows; y++) {
		free(state -> board[y]);
	}

	free(state -> board);
	free(state);
}
