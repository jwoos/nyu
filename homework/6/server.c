#include "server.h"


pthread_mutex_t threadCreateMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t threadCreateCond = PTHREAD_COND_INITIALIZER;
bool threadCreate = false;

pthread_mutex_t threadsMutex = PTHREAD_MUTEX_INITIALIZER;
Vector* threads;

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

	if (mq == NULL) {
		return;
	}

	for (int i = 0; i < threads -> size; i++) {
		Thread* thread = (Thread*) vectorGet(threads, i);

		if (thread -> clientDescriptor > 0) {
			if (shutdown(thread -> clientDescriptor, SHUT_RDWR) < 0) {
				perror("shutdown");
			}

			if (close(thread -> clientDescriptor) < 0) {
				perror("close");
			}
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

// take incoming messages and fan it out
static void* consumer(void* data) {
	int index = *(int*)data;
	println("consumer thread: %d", index);

	int n;
	char message[BUFFER_SIZE + 64];

	handleError(pthread_mutex_lock(mq -> mutex), "pthread_mutex_lock", true);
	while (true) {
		while (mq -> size == 0) {
			handleError(pthread_cond_wait(mq -> cond, mq -> mutex), "pthread_cond_wait", true);
		}

		Message* m = popMessage(mq);
		println("consumer: %s", m -> message);

		handleError(pthread_mutex_lock(&threadsMutex), "pthread_mutex_lock", true);
		for (int i = 0; i < threads -> size; i++) {
			Thread* temp = (Thread*) vectorGet(threads, i);

			// don't send the message back to sender
			if (temp -> id == m -> sender) {
				continue;
			}

			sprintf(message, "[%s:%d] %s", inet_ntoa(temp -> clientAddr.sin_addr), ntohs(temp -> clientAddr.sin_port), m -> message);

			n = write(temp -> clientDescriptor, message, strlen(message));
			if (n < 0) {
				perror("write");
			}
		}
		handleError(pthread_mutex_unlock(&threadsMutex), "pthread_mutex_unlock", true);

		messageDeconstruct(m);
	}

	return NULL;
}

static void* producer(void* data) {
	int index = *(int*)data;
	println("producer thread: %d", index);

	char message[BUFFER_SIZE + 64];

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

	handleError(pthread_mutex_lock(&threadsMutex), "pthread_mutex_lock", true);
	for (int i = 0; i < threads -> size; i++) {
		Thread* temp = (Thread*) vectorGet(threads, i);

		if (temp != thread) {
			sprintf(message, "SERVER: %s:%d has connected\n", inet_ntoa(thread -> clientAddr.sin_addr), ntohs(thread -> clientAddr.sin_port));
			write(temp -> clientDescriptor, message, strlen(message));

			sprintf(message, "SERVER: %s:%d is connected\n", inet_ntoa(temp -> clientAddr.sin_addr), ntohs(temp -> clientAddr.sin_port));
			write(thread -> clientDescriptor, message, strlen(message));
		}
	}
	vectorPush(threads, thread);
	handleError(pthread_mutex_unlock(&threadsMutex), "pthread_mutex_unlock", true);

	println("Connected to client %s:%d", inet_ntoa(thread -> clientAddr.sin_addr), ntohs(thread -> clientAddr.sin_port));

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

		if (n < 0) {
			perror("read");
			continue;
		} else if ((n == 0) || (strncmp(buffer, "/quit", 5) == 0)) {
			println("Connection to client %s:%d closed", inet_ntoa(thread -> clientAddr.sin_addr), ntohs(thread -> clientAddr.sin_port));
			println("");

			// find thread and clean it up
			handleError(pthread_mutex_lock(&threadsMutex), "pthread_mutex_lock", true);
			int toDelete;
			for (int i = 0; i < threads -> size; i++) {
				Thread* temp = (Thread*) vectorGet(threads, i);

				if (temp == thread) {
					toDelete = i;
				} else {
					sprintf(message, "SERVER: %s:%d has disconnected\n", inet_ntoa(thread -> clientAddr.sin_addr), ntohs(thread -> clientAddr.sin_port));
					write(temp -> clientDescriptor, message, strlen(message));
				}
			}
			vectorDelete(threads, toDelete, threadDeconstruct);
			handleError(pthread_mutex_unlock(&threadsMutex), "pthread_mutex_unlock", true);
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

	threads = vectorConstruct(8);
	mq = mqConstruct();

	pthread_t consumerID;
	pthread_t producerID;

	// create consumer thread
	int consumerIndex = 0;
	handleError(pthread_create(&consumerID, NULL, consumer, &consumerIndex), "pthread_create", true);
	handleError(pthread_detach(consumerID), "pthread_detach", true);

	// don't die while waiting for a new connection
	int producerIndex = 0;
	handleError(pthread_mutex_lock(&threadCreateMutex), "pthread_mutex_lock", true);
	while (true) {
		handleError(pthread_create(&producerID, NULL, producer, &producerIndex), "pthread_create", true);
		handleError(pthread_detach(producerID), "pthread_detach", true);

		do {
			/* block until a producer thread has indicated
			 * it is okay to spin up another thread
			 */
			handleError(pthread_cond_wait(&threadCreateCond, &threadCreateMutex), "pthread_cond_wait", true);
		} while (threadCreate != true);
		producerIndex++;
	}
}
