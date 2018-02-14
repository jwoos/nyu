#include "utils.h"


void printUsage(char* msg) {
	printf("%s\n", msg);
	printf("Usage: ./du [FILEPATH]\n");
}

void perrorQuit(char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int ftwHandler(const char* fpath, const struct stat* sbuf, int typeFlag, struct FTW* ftwbuf) {

}
