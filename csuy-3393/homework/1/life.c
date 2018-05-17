#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>


#define DEFAULT_ROWS 10
#define DEFAULT_COLUMNS 10
#define DEFAULT_FILENAME "life.txt"
#define DEFAULT_GENERATIONS 10


typedef struct GameState {
	bool** board;
	uint32_t columns;
	uint32_t rows;
	uint32_t generation;
} GameState;


typedef struct Configuration {
	uint32_t columns;
	uint32_t rows;
	char* filename;
	uint32_t generations;
} Configuration;


void printUsage(void);

Configuration* configurationInitialize(char**, int);

void configurationDeinitialize(Configuration*);

GameState* gameStateInitialize(Configuration*);

uint8_t gameStateNeighborCount(GameState*, uint32_t y, uint32_t x);

void gameStateNext(GameState*);

void gameStatePrint(GameState*);

void gameStateDeinitialize(GameState*);


int main(int argc, char** argv) {
	if (argc > 5) {
		printf("Too many arguments provided\n");
		printUsage();
		exit(EXIT_FAILURE);
	}

	// setup
	Configuration* config = configurationInitialize(argv, argc);
	GameState* state = gameStateInitialize(config);

	uint32_t i = 0;
	do {
		gameStatePrint(state);
		gameStateNext(state);
		i++;
	} while (i <= config -> generations);

	// teardown
	gameStateDeinitialize(state);
	configurationDeinitialize(config);

	return EXIT_SUCCESS;
}

void printUsage(void) {
	printf("Usage: life [rows] [columns] [filename] [generations]\n");
	printf("\trows - the number of rows to work with\n");
	printf("\tcolumns - the number of rows to work with\n");
	printf("\tfilename - the file to use as starting state\n");
	printf("\tgenerations - how many generations to show\n");
}

Configuration* configurationInitialize(char** argv, int argc) {
	Configuration* config = malloc(sizeof(*config));
	if (!config) {
		fprintf(stderr, "Error allocating memory\n");
	}

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
			if (config -> generations <= 0) {
				printf("Invalid generations - must be a positive integer\n");
				printUsage();
				exit(EXIT_FAILURE);
			}

		case 4:
			config -> filename = argv[3];

		case 3:
			config -> columns = strtol(argv[2], NULL, 10);
			if (config -> columns <= 0) {
				printf("Invalid columns - must be a positive integer\n");
				printUsage();
				exit(EXIT_FAILURE);
			}

		case 2:
			config -> rows = strtol(argv[1], NULL, 10);
			if (config -> rows <= 0) {
				printf("Invalid rows - must be a positive integer\n");
				printUsage();
				exit(EXIT_FAILURE);
			}
	}

	return config;
}


void configurationDeinitialize(Configuration* config) {
	free(config);
}

GameState* gameStateInitialize(Configuration* config) {
	GameState* state = malloc(sizeof(*state));
	if (!state) {
		fprintf(stderr, "Error allocating memory\n");
	}
	state -> generation = 0;

	// padding on the edges to deal with cases where the edge is hit
	state -> columns = config -> columns + 2;
	state -> rows = config -> rows + 2;

	/* Initialize the 2D gameboard
	 * Using calloc to zero intialize the entire matrix
	 */
	state -> board = calloc(state -> rows, sizeof(int*));
	if (!state -> board) {
		fprintf(stderr, "Error allocating memory\n");
	}
	for (uint32_t y = 0; y < state -> rows; y++) {
		state -> board[y] = calloc(state -> columns, sizeof(int));
		if (!state -> board[y]) {
			fprintf(stderr, "Error allocating memory\n");
		}
	}

	// read and parse file and use the data to populate state
	FILE* inpuptFile = fopen(config -> filename, "r");
	if (inpuptFile == NULL) {
		printf("unable to open %s", config -> filename);
		printUsage();
		exit(EXIT_FAILURE);
	}

	/* Buffer should be columns + 1
	 * but since columns is padded, we actually have to subtract 1
	 *
	 * command line arguements take precedence over what's in the file
	 */
	char buffer[state -> columns - 1];
	uint32_t rowIndex = 1;
	uint32_t columnIndex = 1;
	while (true) {
		fgets(buffer, state -> columns - 1, inpuptFile);
		if (feof(inpuptFile) || rowIndex >= state -> rows - 1) {
			break;
		}

		bool* row = state -> board[rowIndex];

		while (buffer[columnIndex - 1] != '\0' && buffer[columnIndex - 1] != '\n' && columnIndex < state -> columns - 1) {
			if (buffer[columnIndex - 1] != ' ') {
				row[columnIndex] = true;
			}
			columnIndex++;
		}

		rowIndex++;
		columnIndex = 1;
	}

	fclose(inpuptFile);

	return state;
}

void gameStatePrint(GameState* state) {
	printf("Generation %d:\n", state -> generation);

	for (uint32_t y = 1; y < state -> rows - 1; y++) {
		for (uint32_t x = 1; x < state -> columns - 1; x++) {
			printf("%c", state -> board[y][x] ? '*' : '-');
		}
		printf("\n");
	}

	printf("================================\n");
}

// return the number of live neighbors given a coordinate
uint8_t gameStateNeighborCount(GameState* state, uint32_t y, uint32_t x) {
	uint8_t count = 0;
	/* we don't need to worry about out of bounds
	 * access for the arrays since they're padded
	 * on every side by 1 and we're only subtracting
	 * and adding by 1
	 */

	bool** board = state -> board;

	// top
	if (board[y - 1][x]) {
		count++;
	}

	// bottom
	if (board[y + 1][x]) {
		count++;
	}


	// left
	if (board[y][x - 1]) {
		count++;
	}

	// right
	if (board[y][x + 1]) {
		count++;
	}

	// top left
	if (board[y - 1][x - 1]) {
		count++;
	}

	// top right
	if (board[y - 1][x + 1]) {
		count++;
	}

	// bottom left
	if (board[y + 1][x - 1]) {
		count++;
	}

	// bottom right
	if (board[y + 1][x + 1]) {
		count++;
	}

	return count;
}

void gameStateNext(GameState* state) {
	/* Any live cell with fewer than two live neighbours dies.
	 * Any live cell with two or three live neighbours lives on to the next generation.
	 * Any live cell with more than three live neighbours dies.
	 * Any dead cell with exactly three live neighbours becomes a live cell.
	 */
	bool** localState = calloc(state -> rows, sizeof(int*));
	if (!localState) {
		fprintf(stderr, "Error allocating memory\n");
	}
	for (uint32_t y = 0; y < state -> rows; y++) {
		localState[y] = calloc(state -> columns, sizeof(int));
		if (!localState[y]) {
			fprintf(stderr, "Error allocating memory\n");
		}
		for (uint32_t x = 0; x < state -> columns; x++) {
			localState[y][x] = state -> board[y][x];
		}
	}

	for (uint32_t y = 1; y < state -> rows - 1; y++) {
		for (uint32_t x = 1; x < state -> columns - 1; x++) {
			uint8_t liveCount = gameStateNeighborCount(state, y, x);
			bool current = state -> board[y][x];
			/*printf("state %c %d %d live count %d\n", current ? 't' : 'f', x, y, liveCount);*/

			if (liveCount < 2 || liveCount > 3) {
				localState[y][x] = false;
			} else if (current && (liveCount == 2 || liveCount == 3)) {
				localState[y][x] = true;
			} else if (liveCount == 3) {
				localState[y][x] = true;
			}
		}
	}

	for (uint32_t y = 0; y < state -> rows; y++) {
		free(state -> board[y]);
	}
	free(state -> board);

	// next generation
	state -> board = localState;
	state -> generation++;
}

void gameStateDeinitialize(GameState* state) {
	for (uint32_t y = 0; y < state -> rows; y++) {
		free(state -> board[y]);
	}

	free(state -> board);
	free(state);
}
