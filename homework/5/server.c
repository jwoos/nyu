#include "server.h"


int server(int port) {
	println("server: %d", port);

	// create a TCP socket using IPv4
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket");

		return EXIT_FAILURE;
	}

	// bind to a port
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	struct in_addr ip;
	memset(&ip, 0, sizeof(struct in_addr));
	ip.s_addr = INADDR_ANY;
	addr.sin_addr = ip;

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("bind");

		return EXIT_FAILURE;
	}

	// listen with no backlog
	if (listen(fd, 0) < 0) {
		perror("listen");

		return EXIT_FAILURE;
	}

	// connect to a new client when necessary
	while (true) {
		// connect to a client
		println("Waiting to connect to a client");

		struct sockaddr_in clientAddr;
		unsigned int clientAddrSize;
		if (accept(fd, (struct sockaddr*)&clientAddr, &clientAddrSize) < 0) {
			perror("accept");

			return EXIT_FAILURE;
		}

		println("Connected to client: %s:%d", inet_ntoa(clientAddr.sin_addr), clientAddr.sin_port);

		char buffer[BUFFER_SIZE];

		// set up fd_set each time
		while (true) {
			// set up fd_set
			fd_set descriptors;
			FD_ZERO(&descriptors);

			FD_SET(STDIN_FILENO, &descriptors);
			FD_SET(fd, &descriptors);

			// the fd of the socket will always be greater than stdin
			int selectStatus = select(fd + 1, &descriptors, NULL, NULL, NULL);
			if (selectStatus < 0) {
				perror("select");

				return EXIT_FAILURE;
			} else if (selectStatus) {
				if (FD_ISSET(STDIN_FILENO, &descriptors)) {
					int n;
					n = read(STDIN_FILENO, buffer, READ_SIZE);
					if (n < 0) {
						perror("read");
						continue;
					}
					buffer[n] = '\0';

					n = write(fd, buffer, n + 1);
					if (n < 0) {
						perror("write");
						continue;
					}

					printf("[you] %s", buffer);
				}

				if (FD_ISSET(fd, &descriptors)) {
					int n;
					n = read(STDIN_FILENO, buffer, READ_SIZE);
					if (n < 0) {
						perror("read");
						continue;
					}
					buffer[n] = '\0';

					printf("[%s:%d] %s", inet_ntoa(clientAddr.sin_addr), clientAddr.sin_port, buffer);
				}
			}
		}
	}

	return EXIT_SUCCESS;
}
