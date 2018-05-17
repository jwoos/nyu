#include <stdlib.h>
#include "common.h"
#include <stdio.h>

int main(argc, argv)
     int argc;
     char *argv[];
{
  extern FILE* yyin;

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
  
  init_format();
  (void) yyparse();
  fix_up();
  run(start);
  exit(0);
}
