#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utils.h"


int main(int argc, char** argv) {
	if (argc > 2) {
		printUsage("There can only be one argument");
	}

	char* path;

	if (arg == 1) {
		path = ".";
	} else {
		path = argv[1];
	}

	DIR* dir = opendir(path);
	if (dir == NULL) {
		perrorQuit("Could not open directory");
	}

	unsigned int relativePathSize = 8;
	char* relativePath = calloc(relativePathSize, sizeof(*relativePath));
	if (relativePath == NULL) {
		perrorQuit("Error calling calloc");
	}

	struct dirent* dp = readdir(dir);
	struct stat* sbuf;

	if (errno != 0) {
		perrorQuit("Error reading directory");
	}

	while (dp != NULL) {
		errno = 0;

		int statStatus = lstat(dp -> d_name, sbuf);
		if (statStatus != 0) {
			perror("Error calling lstat");
		}

		if (S_ISDIR(sbuf -> st_mode)) {

		} else {

		}
	}
}
