#ifndef CHAT_THREAD_H
#define CHAT_THREAD_H


#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct Thread {
	pthread_t id;
	char* name;
	struct sockaddr_in clientAddr;
	unsigned int clientAddrSize;
	int clientDescriptor;
} Thread;


Thread* threadConstruct(pthread_t);

void threadDeconstruct(void*);

void threadSetName(Thread*, char*);


#endif
