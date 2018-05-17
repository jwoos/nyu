CC = gcc
CFLAGS = -g -pedantic

LEX = flex

YACC = bison -y
YFLAGS = -d -t

LDFLAGS = -lm

SRC	= syn.c tok.l
OBJ	= syn.o tok.o format.o main.o

massexe: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o massexe $(LDFLAGS)

clean:
	rm -f massexe y.tab.* tok.c *.o

$(OBJ): common.h y.tab.h

y.tab.h:
	$(YACC) $(YFLAGS) syn.y
