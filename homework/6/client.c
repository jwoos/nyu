#include "client.h"


static int fd;
static struct sockaddr_in addr;
static fd_set descriptors;

static void cleanup(void) {
	if (fd > 0) {
		if (shutdown(fd, SHUT_RDWR) < 0) {
			perror("shutdown");
		}

		if (close(fd) < 0) {
			perror("close");
		}
	}
}

// create a TCP socket using IPv4
static void initSocket(void) {
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
}

static void initConnect(char* ip, int port) {
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	struct in_addr ipAddr;
	if (inet_aton(ip, &ipAddr) < 0) {
		perror("inet_aton");
		exit(EXIT_FAILURE);
	}
	addr.sin_addr = ipAddr;

	println("Waiting to connect to server");

	if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("connect");
		exit(EXIT_FAILURE);
	}

	println("Connected to server: %s:%d", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
	println("");
}

static int initSelect(void) {
	FD_ZERO(&descriptors);

	FD_SET(STDIN_FILENO, &descriptors);
	FD_SET(fd, &descriptors);

	int selectStatus = select(FD_SETSIZE, &descriptors, NULL, NULL, NULL);
	if (selectStatus < 0) {
		perror("select");
		exit(EXIT_FAILURE);
	}

	return selectStatus;
}

void client(char* name, char* ip, int port) {
	// register cleanup
	atexit(cleanup);

	println("client: %s@%s:%d", name, ip, port);

	initSocket();

	initConnect(ip, port);

	char buffer[BUFFER_SIZE];
	int n;

	sprintf(buffer, "/name %s", name);
	n = write(fd, buffer, strlen(buffer));
	if (n < 0) {
		perror("write");
	}

	while (true) {
		fflush(stdin);
		memset(&buffer, 0, sizeof(char) * BUFFER_SIZE);

		int selectStatus = initSelect();
		if (selectStatus) {

			if (FD_ISSET(STDIN_FILENO, &descriptors)) {
				if (fgets(buffer, READ_SIZE, stdin) == NULL) {
					perror("getline");

					continue;
				}

				if (strncmp(buffer, "/quit", 5) == 0) {
					println("Exiting");
					break;
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
				} else if (n == 0) {
					println("Connection closed");
					println("Exiting");
					println("");
					break;
				}
				buffer[n] = '\0';

				printf("%s", buffer);
			}
		}
	}
}
