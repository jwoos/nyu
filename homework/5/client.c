#include "client.h"


int client(char* host, int port) {
	println("client: %s:%d", host, port);

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket");

		return EXIT_FAILURE;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	struct in_addr ip;
	if (inet_aton(host, &ip) < 0) {
		perror("inet_aton");

		return EXIT_FAILURE;
	}
	addr.sin_addr = ip;

	println("Waiting to connect to server");
	if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("connect");

		return EXIT_FAILURE;
	}
	println("Connected to server: %s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	println("");

	char buffer[BUFFER_SIZE];

	while (true) {
		fflush(stdin);
		memset(&buffer, 0, sizeof(char) * BUFFER_SIZE);

		fd_set descriptors;
		FD_ZERO(&descriptors);

		FD_SET(STDIN_FILENO, &descriptors);
		FD_SET(fd, &descriptors);

		int selectStatus = select(FD_SETSIZE, &descriptors, NULL, NULL, NULL);
		if (selectStatus < 0) {
			perror("select");

			return EXIT_FAILURE;
		} else if (selectStatus) {
			int n;

			if (FD_ISSET(STDIN_FILENO, &descriptors)) {
				if (fgets(buffer, READ_SIZE, stdin) == NULL) {
					perror("getline");

					continue;
				}

				printf("[you] %s", buffer);

				n = write(fd, buffer, strlen(buffer));
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


				printf("[%s:%d] %s", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), buffer);
			}
		}
	}

	return EXIT_SUCCESS;
}
