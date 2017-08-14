COMPILER = g++
WARNING = -Wall
STANDARD = -std=c++14
DEBUG = -g
OPTIMIZATION = -O0
DIRECTORY = -I.
BASE = $(basename $(FILE))
FILE =
LINK =

default:
	$(COMPILER) ${WARNING} ${STANDARD} ${DEBUG} ${DIRECTORY} ${FILE} ${LINK} -o ${BASE}.out
	./${BASE}.out
