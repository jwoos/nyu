# Compiler; on a Mac gcc or clang are natural choices
CC=gcc

# Compiler flags
#  -pedantic is a gcc-specific; means: complain about EVERYTHING
#  -g is also gcc-family specific; means: include symbol information for debugging
CFLAGS = -g -pedantic

# which scanner generator to use
LEX = flex
# what flags to pass to it
LFLAGS	= -i

# flags for loader 
LDFLAGS = -lm

HEADER	= common.h
SRC	= tok.l 
OBJ	= tok.o scanner-driver.o

scanner-driver	: $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o scanner-driver $(LDFLAGS)

clean	:
	rm -f mass tok.c *.o

$(OBJ)  : common.h $(HEADER)
