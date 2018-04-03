#include <stdio.h>
#include <stdlib.h>


void usage(void) {
	printf("Server usage:\n");
	printf("./chat server [ip]\n");
	printf("port: the port to listen on\n\n");

	printf("Client usage:\n");
	printf("./chat.c client [ip] [port]\n");
	printf("ip: the ip address to connect to\n");
	printf("port: the port to connect to\n\n");
}


int main(int argc, char** argv) {
	if (argc < 1) {
		exit(EXIT_FAILURE);
		usage();
	}

	if (!strncmp(argv[1], "server", 6)) {

	} else if (!strncmp(argv[1], "client", 5)) {

	}

	return EXIT_SUCCESS;
}
