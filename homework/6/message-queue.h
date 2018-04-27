#ifndef CHAT_MESSAGE_QUEUE_H
#define CHAT_MESSAGE_QUEUE_H


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
	pthread_t sender;

	char* message;
	char* host;
	int port;

	struct Message* previous;
	struct Message* next;
} Message;


/* push into tail
 * pop out of head
 */
typedef struct MessageQueue {
	Message* head;
	pthread_mutex_t* headLock;

	pthread_cond_t* cond;

	Message* tail;
	pthread_mutex_t* tailLock;

	int size;
} MessageQueue;


Message* messageConstruct(char*, char*, int);

void messageDeconstruct(Message*);

MessageQueue* mqConstruct(void);

void mqDeconstruct(MessageQueue*);

void pushMessage(MessageQueue*, Message*);

Message* popMessage(MessageQueue*);


#endif
