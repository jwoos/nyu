#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "directory.h"
#include "path.h"
#include "utils.h"
#include "vector.h"


int main(int argc, char** argv) {
	if (argc > 2) {
		printUsage("There can only be one argument");
	}

	char* basePath;

	if (argc == 1) {
		basePath = ".";
	} else {
		/*if ((argv[1][0] != '.' && argv[1][1] !='.') && argv[1][0] != '/')*/
		basePath = join(".", argv[1], '/');
	}

	Path* path = pathConstruct();
	struct stat sbuf;
	struct dirent* dp;
	char* relativePath;
	Directory* directory;

	DIR* dir = opendir(basePath);
	if (dir == NULL) {
		perrorQuit(PERROR_DIRECTORY_OPEN);
	}

	directory = directoryConstruct(basePath, dir);
	pathPush(path, directory);
	relativePath = pathBuild(path);
	dp = readdir(directory -> dir);
	if (errno != 0) {
		perrorQuit(PERROR_DIRECTORY_READ);
	}

	while (path -> directories -> size) {
		// end of directory, go to the next one
		if (dp == NULL) {
			Directory* popped = pathPop(path);

			int size = popped -> size / 1024;
			printf("%d\t%s\n", size, relativePath);

			directoryDeconstruct(popped);

			directory = pathCurrent(path);
			if (directory == NULL) {
				break;
			}
			free(relativePath);
			relativePath = pathBuild(path);
			directory -> size += popped -> size;
			dp = readdir(directory -> dir);
		}

		errno = 0;

		char* fullname = join(relativePath, dp -> d_name, '/');
		int statStatus = stat(fullname, &sbuf);
		free(fullname);

		if (statStatus < 0) {
			perrorQuit(PERROR_STAT);
		}

		mode_t mode = sbuf.st_mode;
		char* name = dp -> d_name;

		// not .. (parent directory)
		if (strncmp(name, "..", 3)) {
			if (S_ISDIR(mode) && strncmp(name, ".", 3)) {
				directory = directoryConstruct(dp -> d_name, NULL);
				pathPush(path, directory);
				free(relativePath);
				relativePath = pathBuild(path);

				dir = opendir(relativePath);
				if (dir == NULL) {
					perrorQuit(PERROR_DIRECTORY_OPEN);
				}

				directory -> dir = dir;
			} else {
				if (sbuf.st_nlink > 1) {
					bool counted = false;

					// linear search
					for (int i = 0; i < path -> accounted -> size; i++) {
						ino_t* expected = vectorGet(path -> accounted, i);

						if (*expected == sbuf.st_ino) {
							counted = true;
							break;
						}
					}

					if (!counted) {
						ino_t* inode = malloc(sizeof(*inode));
						*inode = sbuf.st_ino;
						vectorPush(path -> accounted, inode);
						directory -> size += sbuf.st_size;
					}
				} else {
					directory -> size += sbuf.st_size;
				}
			}
		}

		directory = pathCurrent(path);
		dp = readdir(directory -> dir);
		if (errno != 0) {
			perrorQuit(PERROR_DIRECTORY_READ);
		}
	}

	return 0;
}
