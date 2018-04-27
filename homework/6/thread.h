#ifndef CHAT_THREAD_H
#define CHAT_THREAD_H


#include <stdlib.h>


typedef Thread {
	pthread_t id;
	fd_set descriptors;
	struct sockaddr_in clientAddr;
	int clientDescriptor;
} Thread;


Thread* threadConstruct(pthread_t);

void threadDeconstruct(Thread*);


#endif
