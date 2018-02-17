CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -ggdb -O0

EXECUTABLES = du

all: $(EXECUTABLES)

du: .PHONY
	$(CC) $(CFLAGS) du.c -o $@

memcheck-du: du
	valgrind --leak-check=full ./du

clean:
	rm -f $(EXECUTABLES)

.PHONY:
