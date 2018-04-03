CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -ggdb -O0 -Wno-sign-compare

EXECUTABLES = chat
OBJECTS = chat.o utils.o token.o

all: clean $(EXECUTABLES)

# implicit rule for %.o
# $(CC) $(CPPFLAGS) $(CFLAGS) -c $@

chat: $(OBJECTS)
	$(CC) $(CFLAGS) main.c $^ -o $@

memcheck: chat
	valgrind --leak-check=full --show-leak-kinds=all ./chat

clean:
	touch $(EXECUTABLES) $(OBJECTS) && rm -f $(EXECUTABLES) $(OBJECTS)

.PHONY:
