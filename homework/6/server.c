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
			Message* m = popMessage(mq);
			println("consumer: %s", m -> message);
		}

		while (mq -> size == 0) {
			handleError(pthread_cond_wait(mq -> cond, mq -> mutex), "pthread_cond_wait", true);
		}
	}

	return NULL;
}

static void* producer(void* data) {
	int index = *(int*)data;
	println("producer thread: %d", index);

	Thread* thread = threadConstruct(pthread_self());

	// wait for main thread to release lock
	handleError(pthread_mutex_lock(&threadCreateMutex), "pthread_mutex_lock", true);
	threadCreate = false;

	// connect to a new client
	thread -> clientDescriptor = accept(fd, (struct sockaddr*)&(thread -> clientAddr), &(thread -> clientAddrSize));
	if (thread -> clientDescriptor < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	println("Connected to client: %s:%d", inet_ntoa(thread -> clientAddr.sin_addr), ntohs(thread -> clientAddr.sin_port));

	threadCreate = true;
	handleError(pthread_mutex_unlock(&threadCreateMutex), "pthread_mutex_unlock", true);
	handleError(pthread_cond_broadcast(&threadCreateCond), "pthread_cond_broadcast", true);

	char buffer[BUFFER_SIZE];
	int n;

	/* select is not needed anymore as each connection is
	 * on its own thread so it can block as long as it wants
	 */
	while (true) {
		memset(&buffer, 0, sizeof(char) * BUFFER_SIZE);

		n = read(thread -> clientDescriptor, buffer, READ_SIZE);

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

		Message* m = messageConstruct(thread -> id, buffer, inet_ntoa(thread -> clientAddr.sin_addr), ntohs(thread -> clientAddr.sin_port));
		pushMessage(mq, m);
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
	handleError(pthread_create(&consumerID, NULL, consumer, &consumerIndex), "pthread_create", true);

	// don't die while waiting for a new connection
	int producerIndex = 0;
	handleError(pthread_mutex_lock(&threadCreateMutex), "pthread_mutex_lock", true);
	while (true) {
		handleError(pthread_create(&producerID, NULL, producer, &producerIndex), "pthread_create", true);

		do {
			handleError(pthread_cond_wait(&threadCreateCond, &threadCreateMutex), "pthread_cond_wait", true);
		} while (threadCreate != true);
		producerIndex++;
	}
}
