#include "message-queue.h"


Message* messageConstruct(char* msg, char* host, int port) {
	Message* m = malloc(sizeof(*m));

	m -> message = malloc(sizeof(char) * strlen(msg));
	m -> host = malloc(sizeof(char) * strlen(host));
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
	int s;

	mq -> head = NULL;
	s = pthread_rwlock_init(mq -> headLock, NULL);
	if (s != 0) {
		errno = s;
		perror("pthread_rwlock_init");
		exit(1);
	}

	mq -> tail = NULL;
	s = pthread_rwlock_init(mq -> tailLock, NULL);
	if (s != 0) {
		errno = s;
		perror("pthread_rwlock_init");
		exit(1);
	}

	mq -> size = 0;

	return mq;
}

void mqDeconstruct(MessageQueue* mq) {
	mq -> head = NULL;
	int s;

	s = pthread_rwlock_destroy(mq -> headLock);
	if (s != 0) {
		errno = s;
		perror("pthread_rwlock_destroy");
		exit(1);
	}

	mq -> tail = NULL;
	s = pthread_rwlock_destroy(mq -> tailLock);
	if (s != 0) {
		errno = s;
		perror("pthread_rwlock_destroy");
		exit(1);
	}
}

void lockHead(MessageQueue* mq, int type) {
	int s;

	if (type == WRITE_CODE) {
		s = pthread_rwlock_wrlock(mq -> headLock);
		if (s != 0) {
			errno = s;
			perror("pthread_rw_wrlock");
			exit(1);
		}
	} else {
		s = pthread_rwlock_rdlock(mq -> headLock);
		if (s != 0) {
			errno = s;
			perror("pthread_rw_rdlock");
			exit(1);
		}
	}
}

void unlockHead(MessageQueue* mq) {
	int s = pthread_rwlock_unlock(mq -> headLock);
	if (s != 0) {
		errno = s;
		perror("pthread_rwlock_unlock");
		exit(1);
	}
}

void lockTail(MessageQueue* mq, int type) {
	int s;

	if (type == WRITE_CODE) {
		s = pthread_rwlock_wrlock(mq -> tailLock);
		if (s != 0) {
			errno = s;
			perror("pthread_rw_wrlock");
			exit(1);
		}
	} else {
		s = pthread_rwlock_rdlock(mq -> tailLock);
		if (s != 0) {
			errno = s;
			perror("pthread_rw_rdlock");
			exit(1);
		}
	}
}

void unlockTail(MessageQueue* mq) {
	int s = pthread_rwlock_unlock(mq -> tailLock);
	if (s != 0) {
		errno = s;
		perror("pthread_rwlock_unlock");
		exit(1);
	}
}

void pushMessage(MessageQueue* mq, Message* m) {
	if (mq -> size < 2) {
		lockHead(mq, WRITE_CODE);
		lockTail(mq, WRITE_CODE);

		if (mq -> size == 0) {
			mq -> head = m;
			mq -> tail = m;
		} else {
			mq -> tail -> next = m;
			m -> previous = mq -> tail;
			mq -> tail = m;
		}

		unlockHead(mq);
		unlockTail(mq);
	} else {
		lockTail(mq, WRITE_CODE);

		mq -> tail -> next = m;
		m -> previous = mq -> tail;
		mq -> tail = m;

		unlockTail(mq);
	}

	mq -> size++;
}

Message* popMessage(void) {
}
