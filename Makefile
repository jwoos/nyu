CXX = g++
WARNING = -Wall -Wextra
OPTIMIZE = -O0
DEBUG = -g
STD = -std=c++14
ARGS = $(WARNING) $(OPTIMIZE) $(DEBUG) $(STD)

ALL = utils.o encryption.o

default: clean test

debug-mem-encryption: default
	valgrind --leak-check=full -v ./encryption

debug-mem-main: encryption
	valgrind --leak-check=full -v ./main

main: $(ALL)
	$(CXX) $(ARGS) $@.cpp $^ -o $@

test: $(ALL)
	$(CXX) $(ARGS) $@.cpp $^ -o $@

# Compile into object files
%.o: %.cpp
	$(CXX) $(ARGS) -c $^ -o $@

force:
	touch $(ALL) main encryption test

clean: force
	rm $(ALL) main encryption test
