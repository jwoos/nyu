#include "server.h"


static pthread_mutex_t threadCreateMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t threadCreateCond = PTHREAD_COND_INITIALIZER;
bool threadCreate = false;

MessageQueue* mq;

static int fd;

static void cleanup(void) {
	if (fd > 0) {
		if (shutdown(fd, SHUT_RDWR) < 0) {
			perror("shutdown");
		}

		if (close(fd) < 0) {
			perror("close");
		}
	}

/*
 *    if (clientDescriptor > 0) {
 *        if (shutdown(clientDescriptor, SHUT_RDWR) < 0) {
 *            perror("shutdown");
 *        }
 *
 *        if (close(clientDescriptor) < 0) {
 *            perror("close");
 *        }
 *    }
 */
}

// create a TCP socket using IPv4
static void initSocket(void) {
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
}

// bind to a port
static void initBind(int port) {
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	struct in_addr ip;
	memset(&ip, 0, sizeof(struct in_addr));
	ip.s_addr = htonl(INADDR_ANY);
	addr.sin_addr = ip;

	if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
}

// listen with some backlog
static void initListen(void) {
	if (listen(fd, 5) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
}

bool command(char* input) {
	if (strncmp(input, "/quit", 5) == 0) {
		println("Connection close");
		println("");
		return true;
	}

	return false;
}

// take incoming messages and fan it out
static void* consumer(void* data) {
	int index = *(int*)data;
	println("consumer thread: %d", index);

	while (true) {
		while (mq -> size > 0) {

		}

		while (mq -> size == 0) {
			handleError(pthread_cond_wait(mq -> cond, mq -> headLock), "pthread_cond_wait", true);
		}
	}

	return NULL;
}

static void* producer(void* data) {
	int index = *(int*)data;
	println("producer thread: %d", index);

	// wait for main thread to release lock
	handleError(pthread_mutex_lock(&threadCreateMutex), "pthread_mutex_lock", true);
	threadCreate = false;

	// connect to a new client
	unsigned int clientAddrSize;
	struct sockaddr_in clientAddr;
	fd_set descriptors;
	int clientDescriptor = accept(fd, (struct sockaddr*)&clientAddr, &clientAddrSize);
	if (clientDescriptor < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	println("Connected to client: %s:%d", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

	threadCreate = true;
	handleError(pthread_mutex_unlock(&threadCreateMutex), "pthread_mutex_unlock", true);
	handleError(pthread_cond_broadcast(&threadCreateCond), "pthread_cond_broadcast", true);

	char buffer[BUFFER_SIZE];

	// set up fd_set each time
	while (true) {
		memset(&buffer, 0, sizeof(char) * BUFFER_SIZE);

		// set up fd_set
		FD_ZERO(&descriptors);

		FD_SET(clientDescriptor, &descriptors);

		// the fd of the socket will always be greater than stdin
		int selectStatus = select(FD_SETSIZE, &descriptors, NULL, NULL, NULL);
		if (selectStatus < 0) {
			perror("select");
			exit(EXIT_FAILURE);
		}

		if (selectStatus) {
			int n;

			if (FD_ISSET(clientDescriptor, &descriptors)) {
				n = read(clientDescriptor, buffer, READ_SIZE);

				if (command(buffer)) {
					break;
				}

				if (n < 0) {
					perror("read");
					continue;
				} else if (n == 0) {
					println("Connection closed");
					println("");
					break;
				}
				buffer[n] = '\0';

				printf("[%s:%d] %s", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buffer);
				/*Message* m = messageConstruct(buffer, inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));*/
				/*pushMessage(mq, m);*/
			}
		}
	}

	return NULL;
}

void server(int port) {
	// register cleanup
	atexit(cleanup);

	println("server: %d", port);

	initSocket();

	initBind(port);

	initListen();

	mq = mqConstruct();

	pthread_t consumerID;
	pthread_t producerID;

	// create consumer thread
	int consumerIndex = 0;
	int consumerCreate = pthread_create(&consumerID, NULL, consumer, &consumerIndex);
	if (consumerCreate != 0) {
		errno = consumerCreate;
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	// don't die while waiting for a new connection
	int producerIndex = 0;
	handleError(pthread_mutex_lock(&threadCreateMutex), "pthread_mutex_lock", true);
	while (true) {
		int producerCreate = pthread_create(&producerID, NULL, producer, &producerIndex);
		if (producerCreate != 0) {
			errno = producerCreate;
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}

		do {
			int s = pthread_cond_wait(&threadCreateCond, &threadCreateMutex);
			handleError(s, "pthread_cond_wait", true);
		} while (threadCreate != true);
		producerIndex++;
	}
}
