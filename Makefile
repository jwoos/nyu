WARNING = -Wall
STANDARD = -std=c++14
# certain versions of g++ require 1y instead of specifying 14
# STANDARD = -std=c++1y
DEBUG = -g
OPTIMIZATION = -O0
DIRECTORY = -I.
BASE = $(basename $(FILE))
FILE =
LINK =

default:
	$(CXX) ${WARNING} ${STANDARD} ${DEBUG} ${DIRECTORY} ${FILE} ${LINK} -o ${BASE}.out
	./${BASE}.out
