#include "message-queue.h"


Message* messageConstruct(pthread_t sender, char* msg, char* host, int port) {
	Message* m = malloc(sizeof(*m));
	if (m == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	m -> sender = sender;

	int msgLength = strlen(msg) + 1;
	m -> message = malloc(sizeof(char) * msgLength);
	if (m -> message == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strncpy(m -> message, msg, msgLength);

	int hostLength = strlen(host) + 1;
	m -> host = malloc(sizeof(char) * strlen(host));
	if (m -> host == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strncpy(m -> host, host, hostLength);

	m -> port = port;
	m -> next = NULL;
	m -> previous = NULL;

	return m;
}

void messageDeconstruct(Message* message) {
	free(message -> message);
	free(message -> host);
	free(message);
}

MessageQueue* mqConstruct(void) {
	MessageQueue* mq = malloc(sizeof(*mq));
	if (mq == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	mq -> head = NULL;
	mq -> tail = NULL;

	mq -> mutex = malloc(sizeof(*(mq -> mutex)));
	if (mq -> mutex == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	handleError(pthread_mutex_init(mq -> mutex, NULL), "pthread_mutex_init", true);

	mq -> cond = malloc(sizeof(*(mq -> cond)));
	if (mq -> cond == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	handleError(pthread_cond_init(mq -> cond, NULL), "pthread_cond_init", true);

	mq -> size = 0;

	return mq;
}

void mqDeconstruct(MessageQueue* mq) {
	mq -> head = NULL;

	handleError(pthread_mutex_destroy(mq -> mutex), "pthread_mutex_destroy", true);
	free(mq -> mutex);

	handleError(pthread_cond_destroy(mq -> cond), "pthread_mutex_destroy", true);
	free(mq -> cond);
}

void pushMessage(MessageQueue* mq, Message* m) {
	handleError(pthread_mutex_lock(mq -> mutex), "pthread_mutex_lock", true);

	if (mq -> size < 2) {
		if (mq -> size == 0) {
			mq -> head = m;
			mq -> tail = m;
		} else {
			mq -> tail -> next = m;
			m -> previous = mq -> tail;
			mq -> tail = m;
		}
	} else {
		mq -> tail -> next = m;
		m -> previous = mq -> tail;
		mq -> tail = m;
	}

	mq -> size++;
	handleError(pthread_mutex_unlock(mq -> mutex), "pthread_mutex_unlock", true);
	handleError(pthread_cond_broadcast(mq -> cond), "pthread_cond_broadcast", true);
}

Message* popMessage(MessageQueue* mq) {
	Message* m = mq -> head;
	if (mq -> size <= 2) {
		if (mq -> size == 2) {
			mq -> tail = m;
			mq -> head = m;
			mq -> head -> previous = NULL;
			mq -> head -> next = NULL;

			m -> next = NULL;
			m -> previous = NULL;
		} else {
			mq -> tail = NULL;
			mq -> head = NULL;

			m -> next = NULL;
			m -> previous = NULL;
		}
	} else {
		mq -> head = m -> next;
		mq -> head -> previous = NULL;

		m -> next = NULL;
		m -> previous = NULL;
	}

	mq -> size--;
	return m;
}
