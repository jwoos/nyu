#include "directory.h"


Directory* directoryConstruct(char* name, DIR* dir) {
	Directory* directory = malloc(sizeof(*directory));

	int length = strlen(name) + 1;
	directory -> name = malloc(length * sizeof(char));
	if (directory -> name == NULL) {
		perrorQuit(PERROR_MEMORY);
	}
	strncpy(directory -> name, name, length);

	directory -> size = 4096;
	directory -> dir = dir;

	return directory;
}

void directoryDeconstruct(Directory* directory) {
	free(directory -> name);
	int status = closedir(directory -> dir);
	if (status < 0) {
		perrorQuit(PERROR_DIRECTORY_CLOSE);
	}
	free(directory);
}
