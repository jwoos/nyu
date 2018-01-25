CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -ggdb -O0
LDLIBS =
LDFLAGS =

OBJECTS =
EXECUTABLES = life

default: life

debug-memory: life
	valgrind --leak-check=full -v ./snake

debug-gdb: life
	gdb life

# implicit rule for %.o
# $(CC) $(CPPFLAGS) $(CFLAGS) -c $@

life:
	$(CC) $(CFLAGS) life.c $^ $(LDFLAGS) $(LDLIBS) -o $@

clean:
	rm -f life
