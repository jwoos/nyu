FLAGS = -Wall -std=c99

all: nonblocking nonblocking-for-file

nonblocking: nonblocking.c
	gcc ${FLAGS}  nonblocking.c -o nonblocking

nonblocking-for-file: nonblocking-for-file.c
	gcc ${FLAGS}  nonblocking-for-file.c -o nonblocking-for-file

clean:
	rm -f nonblocking nonblocking-for-file
