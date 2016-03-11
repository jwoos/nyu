COMPILER = g++
WARNING = -Wall
STANDARD = -std=c++11
DEBUG = -g
OPTIMIZATION = -O0
DIRECTORY = -I.
BASE = $(basename $(FILE))

default:
	$(COMPILER) $(WARNING) $(STANDARD) $(DEBUG) $(DIRECTORY) $(FILE) -o $(BASE).out
	./$(BASE).out
