#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "client.h"
#include "server.h"


void usage(bool e) {
	println("Server usage:");
	println("./chat server [port]");
	println("port: the port to listen on");

	println("");

	println("Client usage:");
	println("./chat client name [ip port]");
	println("name: name of the client");
	println("ip: the ip address to connect to");
	println("port: the port to connect to");

	if (e) {
		exit(EXIT_FAILURE);
	}
}



void signalHandler() {
	exit(EXIT_SUCCESS);
}


int main(int argc, char** argv) {
	if (argc < 2) {
		usage(true);
	}

	struct sigaction act;

	act.sa_handler = &signalHandler;
	act.sa_flags = 0;

	if (sigaction(SIGINT, &act, NULL) < 0) {
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

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

		server(port);
	} else if (!strncmp(argv[1], "client", 5)) {
		if (argc != 3 && argc != 5) {
			usage(true);
		}

		char* host;
		int port;
		char* name = argv[2];

		if (argc == 3) {
			host = DEFAULT_HOST;
			port = DEFAULT_PORT;
		} else {
			host = argv[3];
			port = strtol(argv[4], NULL, 10);
		}

		client(name, host, port);
	} else {
		usage(true);
	}

	return EXIT_SUCCESS;
}
