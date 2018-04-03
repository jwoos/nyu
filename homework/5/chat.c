#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "client.h"
#include "server.h"


void usage(bool e) {
	printf("Server usage:\n");
	printf("./chat server [port]\n");
	printf("port: the port to listen on\n\n");

	printf("Client usage:\n");
	printf("./chat client [ip port]\n");
	printf("ip: the ip address to connect to\n");
	printf("port: the port to connect to\n\n");

	if (e) {
		exit(EXIT_FAILURE);
	}
}


int main(int argc, char** argv) {
	if (argc < 2) {
		usage(true);
	}

	int status = EXIT_SUCCESS;

	if (!strncmp(argv[1], "server", 6)) {
		if (argc != 2 && argc != 3) {
			usage(true);
		}

		int port;
		if (argc == 2) {
			port = DEFAULT_PORT;
		} else {
			port = strtol(argv[2], NULL, 10);
		}

		status = server(port);
	} else if (!strncmp(argv[1], "client", 5)) {
		if (argc != 2 && argc != 4) {
			usage(true);
		}

		char* host;
		int port;

		if (argc == 2) {
			host = DEFAULT_HOST;
			port = DEFAULT_PORT;
		} else {
			host = argv[3];
			port = strtol(argv[4], NULL, 10);
		}

		status = client(host, port);
	} else {
		usage(true);
	}

	return status;
}
