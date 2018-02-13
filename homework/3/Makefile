CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -ggdb -O0

EXECUTABLES = du du_nftw

all: $(EXECUTABLES)

du: .PHONY
	$(CC) $(CFLAGS) du.c -o $@

du_nftw: .PHONY
	$(CC) $(CFLAGS) du_nftw.c -o $@

memcheck-du: du
	valgrind --leak-check=full ./du

memcheck-du_nftw: du_nftw
	valgrind --leak-check=full ./du_nftw

clean:
	rm -f $(EXECUTABLES)

.PHONY:
