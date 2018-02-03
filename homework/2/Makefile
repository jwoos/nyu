CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -ggdb -O0 -D_GNU_SOURCE

EXECUTABLES = env

env: .PHONY
	$(CC) $(CFLAGS) env.c -o $@

memcheck: env
	valgrind --leak-check=full ./env

clean:
	rm -f $(EXECUTABLES)

.PHONY:
