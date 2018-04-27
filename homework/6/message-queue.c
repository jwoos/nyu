#include "message-queue.h"


Message* messageConstruct(char* msg, char* host, int port) {
	Message* m = malloc(sizeof(*m));
	if (m == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

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
	mq -> headLock = malloc(sizeof(*(mq -> headLock)));
	if (mq -> headLock == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	handleError(pthread_mutex_init(mq -> headLock, NULL), "pthread_mutex_init", true);

	mq -> cond = malloc(sizeof(*(mq -> cond)));
	if (mq -> cond == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	handleError(pthread_cond_init(mq -> cond, NULL), "pthread_cond_init", true);

	mq -> tail = NULL;
	mq -> tailLock = malloc(sizeof(*(mq -> tailLock)));
	if (mq -> tailLock == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	handleError(pthread_mutex_init(mq -> tailLock, NULL), "pthread_mutex_init", true);

	mq -> size = 0;

	return mq;
}

void mqDeconstruct(MessageQueue* mq) {
	mq -> head = NULL;

	handleError(pthread_mutex_destroy(mq -> headLock), "pthread_mutex_destroy", true);
	free(mq -> headLock);

	handleError(pthread_cond_destroy(mq -> cond), "pthread_mutex_destroy", true);

	handleError(pthread_mutex_destroy(mq -> tailLock), "pthread_mutex_destroy", true);
	free(mq -> tailLock);
}

void pushMessage(MessageQueue* mq, Message* m) {
	if (mq -> size < 2) {
		handleError(pthread_mutex_lock(mq -> headLock), "pthread_mutex_lock", true);
		handleError(pthread_mutex_lock(mq -> tailLock), "pthread_mutex_lock", true);

		if (mq -> size == 0) {
			mq -> head = m;
			mq -> tail = m;
		} else {
			mq -> tail -> next = m;
			m -> previous = mq -> tail;
			mq -> tail = m;
		}

		mq -> size++;

		handleError(pthread_mutex_unlock(mq -> headLock), "pthread_mutex_unlock", true);
		handleError(pthread_mutex_unlock(mq -> tailLock), "pthread_mutex_unlock", true);
	} else {
		handleError(pthread_mutex_lock(mq -> headLock), "pthread_mutex_lock", true);

		mq -> tail -> next = m;
		m -> previous = mq -> tail;
		mq -> tail = m;

		mq -> size++;
		handleError(pthread_mutex_unlock(mq -> headLock), "pthread_mutex_unlock", true);
	}
	handleError(pthread_cond_broadcast(mq -> cond), "pthread_cond_broadcast", true);
}

Message* popMessage(MessageQueue* mq) {
	if (mq -> size < 2) {
		handleError(pthread_mutex_lock(mq -> headLock), "pthread_mutex_lock", true);
		handleError(pthread_mutex_lock(mq -> tailLock), "pthread_mutex_lock", true);

		handleError(pthread_mutex_unlock(mq -> headLock), "pthread_mutex_unlock", true);
		handleError(pthread_mutex_unlock(mq -> tailLock), "pthread_mutex_unlock", true);
	} else {
		handleError(pthread_mutex_lock(mq -> headLock), "pthread_mutex_lock", true);

		handleError(pthread_mutex_unlock(mq -> headLock), "pthread_mutex_unlock", true);
	}
}
