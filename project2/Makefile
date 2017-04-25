CXX = g++
CXXFLAGS = -Wall -Wextra -O0 -g -std=c++14
LDLIBS = -lcryptopp

OBJECTS = utils.o wrapper.o

default: clean main

main: $(OBJECTS)

test: $(OBJECTS)

.PHONY: clean

clean:
	touch main test $(OBJECTS) && rm main test *.o
