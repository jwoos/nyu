#ifndef CHAT_COMMON_H
#define CHAT_COMMON_H


#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"
#include "utils.h"


typedef struct Message {
	char* message;
	char* host;
	int port;
} Message;


typedef struct MessageQueue {
	Message* head;
	pthread_mutex_t* headLock;

	Message* tail;
	pthread_mutex_t* tailLock;
} MessageQueue;


Message* messageConstruct(char*, char*, int);

void messageDeconstruct(Message*);

MessageQueue* mqConstruct(void);

void mqDeconstruct(MessageQueue*);


#endif
