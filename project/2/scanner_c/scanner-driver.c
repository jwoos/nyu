#include <stdlib.h>
#include "common.h"
#include <stdio.h>

YYSTYPE yylval; /* A *global* value to pass current token attributes. */

/* This table really should be either mechanically generated or in a separate file. */
char* tok_table[102]={NULL};

void init_table()
{
  tok_table[0]="EOF"; /* Lex convention: 0 is the end of the file. */
  tok_table[KW_INT]="int";
  tok_table[KW_FLOAT]="float";
  tok_table[KW_IF]="if";
  tok_table[KW_ELSE]="else";
  tok_table[KW_WHILE]="while";
  tok_table[KW_RETURN]="return";
  tok_table[KW_READ]="read";
  tok_table[KW_WRITE]="write";
  tok_table[OP_PLUS]="+";
  tok_table[OP_MINUS]="-";
  tok_table[OP_MULT]="*";
  tok_table[OP_DIV]="/";
  tok_table[OP_ASSIGN]="=";
  tok_table[OP_EQ]="==";
  tok_table[OP_LT]="<";
  tok_table[OP_LE]="<=";
  tok_table[OP_GT]=">";
  tok_table[OP_GE]=">=";
  tok_table[LPAR]="(";
  tok_table[RPAR]=")";
  tok_table[LBRACE]="{";
  tok_table[LBRACE]="}";
  tok_table[SEMICOLON]=";";
  tok_table[COMMA]=",";
  tok_table[ID]="identifier";
  tok_table[INT_LIT]="integer literal";
  tok_table[FLOAT_LIT]="float literal";
  tok_table[STRING_LIT]="float literal";
  tok_table[WS_TOKEN]="white space"; /* not really a token; should not returned from scanner */
  tok_table[NL_TOKEN]="new line"; /* not really a token; should not returned from scanner */
}


int main(argc, argv)
     int argc;
     char *argv[];
{
  extern FILE* yyin;

  init_table();
  
  if (argc != 2)
    {
      fprintf(stderr,"\n\t\tUsage:\t%s filename\n", argv[0]);
      exit(1);
    }
  else if (!(yyin=fopen(argv[1],"r")))
    {
      fprintf(stderr,"%s: cannot open '%s'.\n", argv[0], argv[1]);
      exit(1);
    }

  printf("Token\tToken\tValue\nnumber\tname\n");

  int next_token;

  /* weird double parentheses are to shut up a gcc warning */
  while ((next_token=yylex()))
    {
      printf ("%d\t%s\t", next_token, tok_table[next_token]);
      if (next_token==ID)
	printf ("\"%s\"",yylval.ptr);
      if (next_token==INT_LIT)
	printf ("\"%d\"",yylval.value);
      if (next_token==FLOAT_LIT)
	printf ("\"%f\"",yylval.valuef);
      if (next_token==STRING_LIT)
	printf ("\"%s\"",yylval.ptr);
      printf("\n");
    }
  printf("Found EOF. Stopping.\n");
  exit(0);
}
