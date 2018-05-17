%{
/*
 * tok.l
 *
 * flex input file for mass (MICRO+ assembler)
 *
 */

#include <stdlib.h>
#include <strings.h>
#ifdef ANSI_C
extern char *strdup(char *);
#else
extern char *strdup();
#endif
#include <stdio.h>
#include "common.h"
#ifdef MSDOS
#include "y_tab.h"
#else
#include "y.tab.h"
#endif
char op_name[20];
int line_no = 1;
char *skip;
int mylength;

#define save_return(x) {strncpy(op_name,yytext,19); op_name[19]='\0'; yylval.u.value=x-ADD; return(x);}

%}

%%

"//".*			{/* skip comments */} 
ADD			save_return(ADD);
ADDF			save_return(ADDF);
SUB			save_return(SUB);
SUBF			save_return(SUBF);
MUL			save_return(MUL);
MULF			save_return(MULF);
DIV			save_return(DIV);
DIVF			save_return(DIVF);
NEG			save_return(NEG);
NEGF			save_return(NEGF);
COPY			save_return(COPY);
COPYF			save_return(COPYF);
LABEL			save_return(LABEL);
JUMP			save_return(JUMP);
JEQ			save_return(JEQ);
JEQF			save_return(JEQF);
JNE			save_return(JNE);
JNEF			save_return(JNEF);
JLT			save_return(JLT);
JLTF			save_return(JLTF);
JLE			save_return(JLE);
JLEF			save_return(JLEF);
JGE			save_return(JGE);
JGEF			save_return(JGEF);
JGT			save_return(JGT);
JGTF			save_return(JGTF);
CALL			save_return(CALL);
RETURN			save_return(RETURN);
READ			save_return(READ);
READF			save_return(READF);
WRITE			save_return(WRITE);
WRITEF			save_return(WRITEF);
WRITES			save_return(WRITES);
NEWLINE			save_return(NEWLINE);
START			save_return(START);
STOP			save_return(STOP);
PUSH                    save_return(PUSH);
PUSHF                   save_return(PUSHF);
POP                     save_return(POP);
sqrt			{ yylval.kind=SYMB; yylval.u.value=FN_SQRT; return(SYMBOL); }
exp			{ yylval.kind=SYMB; yylval.u.value=FN_EXP; return(SYMBOL); }
log			{ yylval.kind=SYMB; yylval.u.value=FN_LOG; return(SYMBOL); }
[a-z][a-z0-9#]*         {
  			  fprintf(stderr,
				  "Unexpected symbol <%s> in line %d.\n",
				  yytext,
				  line_no);
			}
[,\t ]+			{} /*return(WS);*/
[0-9]+			{ for (mylength=yyleng, skip=yytext;
			       *skip =='0';
			       skip++, mylength--)
			    ;
			  if (mylength>6) 
			    {
			      fprintf(stderr,
				      "Suspiciously large number %s in line %d. Replacing by 0.\n",
				      skip, line_no);
			      yylval.kind=ADDR;
			      yylval.u.value=0;
			    }
			  else 
			    {
			      yylval.kind=ADDR;
			      yylval.u.value=(int)atol(skip);
			    }
			  return (ADDRESS);
			}

"@"[0-9]+		{ for (mylength=yyleng-1, skip=yytext+1;
			       *skip =='0';
			       skip++, mylength--)
			    ;
			  if (mylength>6) 
			    {
			      fprintf(stderr,
				      "Suspiciously large number %s in line %d. Replacing by 0.\n",
				      skip, line_no);
			      yylval.kind=INDIRECT;
			      yylval.u.value=0;
			    }
			  else 
			    {
			      yylval.kind=INDIRECT;
			      yylval.u.value=(int)atol(skip);
			    }
			  return (INDIR);
			}

"#""-"?[0-9]+		{ for (mylength=yyleng--, skip=yytext+1;
			       *skip =='0';
			       skip++, mylength--)
			    ;
			  if (mylength>6) 
			    {
			      fprintf(stderr,
				      "Suspiciously large constant %s in line %d. Replacing by 0.\n",
				      skip, line_no);
			      yylval.kind=CONST;
			      yylval.u.value=0;
			    }
			  else 
			    {
			      yylval.kind=CONST;
			      yylval.u.value=(int)atol(skip);
			    }
			  return (CONSTANT);
			}

"#"[-+]?([0-9]*([0-9]"."|"."[0-9])[0-9]*|[0-9]+)([eE][-+]?[0-9]+)? {
	                  yylval.kind=CONSTF;
			  yylval.u.valuef=atof(yytext+1);
			  return (CONSTANTF);
			}

\"[^\"]*\"		{
			   yylval.kind=STR;
			   yytext[yyleng-1]='\0';
			   yylval.u.ptr=strdup(yytext+1);
			   return(STRING);
			}

\n			{ line_no++; return(NL); }
.			{ fprintf (stderr,
				   "Illegal or out of place character '%c (0x%x)' on line %d.\n",
				   yytext[0], yytext[0], line_no);
			}

%%
int yywrap ()
{
	return (1);
}
