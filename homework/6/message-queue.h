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


#define WRITE_CODE 1
#define READ_CODE 2


typedef struct Message {
	char* message;
	char* host;
	int port;

	struct Message* previous;
	struct Message* next;
} Message;


typedef struct MessageQueue {
	Message* head;
	pthread_rwlock_t* headLock;

	Message* tail;
	pthread_rwlock_t* tailLock;

	int size;
} MessageQueue;


Message* messageConstruct(char*, char*, int);

void messageDeconstruct(Message*);

MessageQueue* mqConstruct(void);

void mqDeconstruct(MessageQueue*);

void lockHead(MessageQueue*, int);

void unlockHead(MessageQueue*);

void lockTail(MessageQueue*, int);

void unlockTail(MessageQueue*);

void pushMessage(MessageQueue*, Message*);

Message* popMessage(void);


#endif
