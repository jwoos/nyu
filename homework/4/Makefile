CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -ggdb -O0

EXECUTABLES = shell
OBJECTS = shell.o utils.o token.o

all: clean $(EXECUTABLES)

# implicit rule for %.o
# $(CC) $(CPPFLAGS) $(CFLAGS) -c $@

shell: $(OBJECTS)
	$(CC) $(CFLAGS) main.c $^ -o $@

memcheck: shell
	valgrind --leak-check=full --show-leak-kinds=all ./shell

clean:
	touch $(EXECUTABLES) $(OBJECTS) && rm -f $(EXECUTABLES) $(OBJECTS)

.PHONY:
