#include "message-queue.h"


Message* messageConstruct(char* msg, char* host, int port) {
	Message* m = malloc(sizeof(*m));

	m -> message = malloc(sizeof(char) * strlen(msg));
	m -> host = malloc(sizeof(char) * strlen(host));
	m -> port = port;

	return m;
}

void messageDeconstruct(Message* message) {
	free(message -> message);
	free(message -> host);
	free(message);
}

MessageQueue* mqConstruct(void) {
	MessageQueue* mq = malloc(sizeof(*mq));
	int s;

	mq -> head = NULL;
	s = pthread_mutex_init(mq -> headLock, NULL);
	if (s != 0) {
		errno = s;
		perror("pthread_mutex_init");
		exit(1);
	}

	mq -> tail = NULL;
	s = pthread_mutex_init(mq -> tailLock, NULL);
	if (s != 0) {
		errno = s;
		perror("pthread_mutex_init");
		exit(1);
	}

	return mq;
}

void mqDeconstruct(MessageQueue* mq) {
	mq -> head = NULL;
	int s;

	s = pthread_mutex_destroy(mq -> headLock);
	if (s != 0) {
		errno = s;
		perror("pthread_mutex_destroy");
		exit(1);
	}

	mq -> tail = NULL;
	s = pthread_mutex_destroy(mq -> tailLock);
	if (s != 0) {
		errno = s;
		perror("pthread_mutex_destroy");
		exit(1);
	}
}
