CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -ggdb -O0

EXECUTABLES = du du_ntfw

all: $(EXECUTABLES)

du: .PHONY
	$(CC) $(CFLAGS) du.c -o $@

du_ntfw: .PHONY
	$(CC) $(CFLAGS) du_ntfw.c -o $@

memcheck-du: du
	valgrind --leak-check=full ./du

memcheck-du_ntfw: du_ntfw
	valgrind --leak-check=full ./du_ntfw

clean:
	rm -f $(EXECUTABLES)

.PHONY:
