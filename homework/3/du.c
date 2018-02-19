#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


#define DEFAULT_CAPACITY 16

#define PERROR_MEMORY "Error allocating memory"
#define PERROR_DIRECTORY "Error with directory"
#define PERROR_STAT "Error calling stat"


void printUsage(char*);

void perrorQuit(char*);

typedef struct Directory {
	char* name;
	int size;
} Directory;

typedef struct Path {
	char** path;
	int pathSize;
	int pathCapacity;

	Directory* directories;
	int directoriesSize;
	int directoriesCapacity;

	inode_t* accounted;
} Path;

Directory* directoryConstruct(char*);

void directoryDeconstruct(Directory*);

void directoryAddSize(Directory*, int);

Path* pathConstruct(char*);

void pathDeconstruct(Path*);

void pathPush(Path*, char*);

char* pathPop(Path*);


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
		perrorQuit(PERROR_DIRECTORY);
	}

	Path* path = pathConstruct(basePath);

	/* ino_t  d_ino       File serial number
	 * char   d_name[]    Filename string of entry.
	 */
	struct dirent* dp = readdir(dir);
	/* dev_t st_dev            Device ID of device containing file.
	 * ino_t st_ino            File serial number.
	 * mode_t st_mode          Mode of file (see below).
	 * nlink_t st_nlink        Number of hard links to the file.
	 * uid_t st_uid            User ID of file.
	 * gid_t st_gid            Group ID of file.
	 * dev_t st_rdev           Device ID (if file is character or block special).
	 * off_t st_size           For regular files, the file size in bytes.
	 *                         For symbolic links, the length in bytes of the
	 *                         pathname contained in the symbolic link.
	 *                         For a shared memory object, the length in bytes.
	 *                         For a typed memory object, the length in bytes.
	 *                         For other file types, the use of this field is
	 *                         unspecified.
	 * struct timespec st_atim Last data access timestamp.
	 * struct timespec st_mtim Last data modification timestamp.
	 * struct timespec st_ctim Last file status change timestamp.
	 * blksize_t st_blksize    A file system-specific preferred I/O block size for this object. In some file system types, this
	 *                         may vary from file to file.
	 * blkcnt_t st_blocks      Number of blocks allocated for this object.
	*/
	struct stat sbuf;

	if (errno != 0) {
		perrorQuit(PERROR_DIRECTORY);
	}

	while (dp != NULL) {
		errno = 0;

		int statStatus = stat(dp -> d_name, &sbuf);
		if (statStatus != 0) {
			perror(PERROR_STAT);
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

Directory* directoryConstruct(char* name) {
	Directory* dir = malloc(sizeof(*dir));

	int length = strlen(name) + 1;
	dir -> name = malloc(length * sizeof(char));
	if (dir -> name == NULL) {
		perrorQuit(PERROR_MEMORY);
	}
	strncpy(dir -> name, name, length);

	dir -> size = 0;

	return dir;
}

void directoryDeconstruct(Directory* dir) {
	free(dir -> name);
	free(dir);
}

void directoryAddSize(Directory* dir, int size) {
	dir -> size += size;
}

Path* pathConstruct(char* base) {
	Path* path = mallc(sizeof(*path));

	path -> path = calloc(DEFAULT_CAPACITY, sizeof(char*));
	if (path -> path == NULL) {
		perrorQuit(PERROR_MEMORY);
	}
	int length = strlen(base) + 1;
	path -> path[0] = malloc(length * sizeof(char));
	if (path -> path[0] == NULL) {
		perrorQuit(PERROR_MEMORY);
	}
	strncpy(path -> path[0], base, length);


	path -> directories = calloc(DEFAULT_CAPACITY, sizeof(Directory));
	if (path -> directories == NULL) {
		perrorQuit(PERROR_MEMORY);
	}
	path -> directoriesSize = 0;
	path -> directoriesCapacity = DEFAULT_CAPACITY;

	return path;
}

void pathDeconstruct(Path* path) {
	for (int i = 0; i < dir -> pathSize; i++) {
		free(path -> path[i]);
	}
	free(path -> path);

	for (int i = 0; i < dir -> directoriesSize; i++) {
		directoryDeconstruct(path -> directories + i);
	}
	free(path -> directories);

	free(path -> accounted);

	free(path);
}

void pathPush(Path* path, char* dir) {
}

char* pathPop(Path* path) {

}
