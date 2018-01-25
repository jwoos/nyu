CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -ggdb -O0
LDLIBS = $(LDLIBS)
LDFLAGS = $(LDFLAGS)

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
	$(CC) life.c $^ $(LDFLAGS) $(LDLIBS) -o $@

clean:
	rm -f life
