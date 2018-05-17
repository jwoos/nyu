#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H


#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/ip.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "common.h"
#include "utils.h"
#include "message-queue.h"
#include "thread.h"
#include "vector.h"


void server(int);


#endif
