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
	addr.sin_port = htons(port);
	struct in_addr ip;
	memset(&ip, 0, sizeof(struct in_addr));
	ip.s_addr = INADDR_ANY;
	addr.sin_addr = ip;

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("bind");

		return EXIT_FAILURE;
	}

	// listen with no backlog
	if (listen(fd, 1) < 0) {
		perror("listen");

		return EXIT_FAILURE;
	}

	// make stdin nonblocking
	int flags = fcntl(STDIN_FILENO, F_GETFL);
	flags |= O_NONBLOCK;
	fcntl(STDIN_FILENO, F_SETFL, flags);

	// connect to a new client when necessary
	while (true) {
		// connect to a client
		println("Waiting to connect to client");

		struct sockaddr_in clientAddr;
		unsigned int clientAddrSize;
		if (accept(fd, (struct sockaddr*)&clientAddr, &clientAddrSize) < 0) {
			perror("accept");

			return EXIT_FAILURE;
		}

		println("Connected to client: %s:%d", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
		println("");

		char buffer[BUFFER_SIZE];

		// set up fd_set each time
		while (true) {
			// set up fd_set
			fd_set descriptors;
			FD_ZERO(&descriptors);

			FD_SET(STDIN_FILENO, &descriptors);
			FD_SET(fd, &descriptors);

			// the fd of the socket will always be greater than stdin
			int selectStatus = select(FD_SETSIZE, &descriptors, NULL, NULL, NULL);
			if (selectStatus < 0) {
				perror("select");

				return EXIT_FAILURE;
			} else if (selectStatus) {
				int n;

				if (FD_ISSET(STDIN_FILENO, &descriptors)) {
					n = read(STDIN_FILENO, buffer, READ_SIZE);
					if (n < 0) {
						if (errno == EAGAIN) {
							errno = 0;
							continue;
						}
						perror("read");
						continue;
					}
					buffer[n] = '\0';

					printf("[you] %s", buffer);

					n = write(fd, buffer, n + 1);
					if (n < 0) {
						perror("write");
						continue;
					}
				}

				if (FD_ISSET(fd, &descriptors)) {
					n = read(fd, buffer, READ_SIZE);
					if (n < 0) {
						perror("read");
						continue;
					}
					buffer[n] = '\0';

					printf("[%s:%d] %s", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buffer);
				}
			}
		}
	}

	return EXIT_SUCCESS;
}
