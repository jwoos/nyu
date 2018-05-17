CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -ggdb -O0

EXECUTABLES = life

life: .PHONY
	$(CC) $(CFLAGS) life.c -o $@

memcheck: life
	valgrind --leak-check=full ./life

clean:
	rm -f $(EXECUTABLES)

.PHONY:
