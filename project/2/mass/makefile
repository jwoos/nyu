CC=gcc
CFLAGS = -g -pedantic
LEX = flex
YACC = bison -y
YFLAGS	= -d -t
# CFLAGS	= -O
LFLAGS	= -i
LDFLAGS = -lm

SRC	= syn.c tok.l 
OBJ	= syn.o tok.o format.o main.o

mass	: $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o mass $(LDFLAGS)

clean	:
	rm -f mass y.tab.* tok.c *.o

$(OBJ)  : common.h y.tab.h

y.tab.h : syn.y
