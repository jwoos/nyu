%{
/*
 * syn.y
 *
 * mass (Micro+ assembler)  grammar in Yacc format.
 */

#include "common.h"
static int error_line= -1;
  
      
%}

%token ADD ADDF MUL MULF DIV DIVF SUB SUBF NEG NEGF COPY COPYF LABEL
%token JUMP JEQ JEQF JNE JNEF JLT JLTF JLE JLEF JGE JGEF JGT JGTF
%token CALL RETURN  READ READF WRITE WRITEF WRITES NEWLINE STOP START
%token PUSH PUSHF POP
%token NL ADDRESS CONSTANT CONSTANTF INDIR STRING SYMBOL

%%
file :  file line  {}
	|	   {}
	;

line :  opcode op op op NL 
		{ insert(3,$1.u.value,$2,$3,$4); }
     |   opcode  op  op  NL 
		{ insert(2,$1.u.value,$2,$3,DUMMY); }
     |   opcode   op  NL 
		{ insert(1,$1.u.value,$2,DUMMY,DUMMY); }
     |   opcode  NL 
		{ insert(0,$1.u.value,DUMMY,DUMMY,DUMMY); }
     |  NL 	{}

     |  WRITES STRING
		{ 
		  insert(1,$1.u.value,$2,DUMMY,DUMMY);
		}

     |  error NL
		{ if (line_no-1 != error_line)
		    fprintf(stderr,"I do not understand line %d.\n",line_no-1);
		  error_line = line_no-1;
		  yyerrok; }
     ;
opcode  : ADD
	| ADDF
	| SUB
	| SUBF
	| MUL
	| MULF
	| DIV
	| DIVF
	| JNE
	| JNEF
	| JEQ
	| JEQF
	| JGT
	| JGTF
	| JGE
	| JGEF
	| JLT
	| JLTF
	| JLE
	| JLEF
	| COPY
	| COPYF
	| NEG
	| NEGF
        | LABEL
	| JUMP
	| CALL
	| RETURN
        | READ
        | READF
	| WRITE
	| WRITEF
	| WRITES
	| NEWLINE
	| STOP
	| START
  	| PUSH
  	| PUSHF
	| POP
	;

op : ADDRESS
   | CONSTANT
   | CONSTANTF
   | INDIR
   | SYMBOL
   ;
%%

#include <stdio.h>

extern char yytext[];

int yyerror(s)
char *s;
{
  if (line_no != error_line) 
    fprintf(stderr, "%s on line %d.\n", s, line_no);

  error_line=line_no;
  return 0; // Not sure if the return value is used anywhere.
}
