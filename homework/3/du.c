#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


void printUsage(char*);

void perrorQuit(char*);

typedef struct Path {
	char* base;
	int baseSize;
	int baseMax;

	int directoriesSize;
	int directoriesMax;
	char** directories;
} Path;

void buildPath(char**, int, char*);


int main(int argc, char** argv) {
	if (argc > 2) {
		printUsage("There can only be one argument");
	}

	char* basePath;

	if (argc == 1) {
		basePath = "./";
	} else {
		basePath = argv[1];
	}

	DIR* dir = opendir(basePath);
	if (dir == NULL) {
		perrorQuit("Could not open directory");
	}

	unsigned int pathSize = 16;
	char* path = calloc(relativePathSize, sizeof(*path));
	if (path == NULL) {
		perrorQuit("Error calling calloc");
	}

	struct dirent* dp = readdir(dir);
	struct stat sbuf;

	if (errno != 0) {
		perrorQuit("Error reading directory");
	}

	while (dp != NULL) {
		errno = 0;

		int statStatus = stat(dp -> d_name, &sbuf);
		if (statStatus != 0) {
			perror("Error calling stat");
		}

		mode_t mode = sbuf.st_mode;
		char* name = dp -> d_name;


		if (!(strncmp(name, ".", 2)) || !(strncmp(name, "..", 3))) {
			printf("child or parent\n");
		} else {
			printf("name: %s", name);
			if (S_ISDIR(mode)) {
				printf(" directory\n");
			} else if (S_ISLNK(mode)) {
				printf(" is symlink\n");
			} else {
				printf(" size: %ld\n", sbuf.st_size);
			}
		}

		dp = readdir(dir);
	}
}


void printUsage(char* msg) {
	printf("%s\n", msg);
	printf("Usage: ./du [FILEPATH]\n");
}

void perrorQuit(char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

void buildPath(char** path, int size, char* name) {
	int addLength = strlen(name);
}
