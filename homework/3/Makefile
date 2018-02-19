CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -ggdb -O0

EXECUTABLES = du
OBJECTS = directory.o path.o utils.o vector.o

all: clean $(EXECUTABLES)

# implicit rule for %.o
# $(CC) $(CPPFLAGS) $(CFLAGS) -c $@

du: $(OBJECTS)
	$(CC) $(CFLAGS) du.c $^ -o $@

memcheck-du: du
	valgrind --leak-check=full ./du

clean:
	touch $(EXECUTABLES) $(OBJECTS) && rm -f $(EXECUTABLES) $(OBJECTS)

.PHONY:
