CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -ggdb -O0 -Wno-sign-compare -pthread

EXECUTABLES = chat
OBJECTS = utils.o client.o server.o message-queue.o thread.o

all: clean $(EXECUTABLES)

# implicit rule for %.o
# $(CC) $(CPPFLAGS) $(CFLAGS) -c $@

chat: $(OBJECTS)
	$(CC) $(CFLAGS) chat.c $^ -o $@

memcheck: chat
	valgrind --leak-check=full --show-leak-kinds=all ./chat

clean:
	touch $(EXECUTABLES) $(OBJECTS) && rm -f $(EXECUTABLES) $(OBJECTS)

.PHONY:
