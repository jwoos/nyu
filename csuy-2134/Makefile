WARNING = -Wall
STANDARD = -std=c++14
# certain versions of g++ require 1y instead of specifying 14
# STANDARD = -std=c++1y
DEBUG = -g
OPTIMIZATION = -O0
DIRECTORY =
BASE = $(basename ${FILE})
FILE =
LINK =
LINK_PREFIXED = $(addprefix ${DIRECTORY}, ${LINK})

default:
	${CXX} ${WARNING} ${STANDARD} ${DEBUG} ${DIRECTORY}${FILE} ${LINK_PREFIXED} -o ${DIRECTORY}${BASE}.out
	./${DIRECTORY}${BASE}.out

object:
	${CXX} -Wall -g -O0 -std=c++14 -c ${DIRECTORY}${FILE} -o ${DIRECTORY}${BASE}.o
