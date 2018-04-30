#define NONE 0x0
#define LBL  0x3 /* !!! */
#define ADDR 0x2
#define CONST 0x4
#define CONSTF 0x8
#define INDIRECT 0x10
#define STR 0x20
#define SYMB 0x40
#define SRC (ADDR|CONST|INDIRECT)
#define SRCF (ADDR|CONST|CONSTF|INDIRECT)
#define TARGET (ADDR|INDIRECT)
#define TARGETF (ADDR|INDIRECT|0x40) /* Special flag to force the */
				     /* result to floating point  */

#define FN_SQRT 1
#define FN_EXP 2
#define FN_LOG 3

extern void insert();
extern void fix_up();
extern void init_format();
extern int line_no;
extern char op_name[20];
extern int start;
extern int no_labels;
extern int icount;

#define YYSTYPE thing

typedef struct
  {
    int kind;
    union {int value; float valuef; char *ptr;} u;
  } thing;
      
extern YYSTYPE yylval;

extern thing DUMMY;

void run(int);
int yylex (void);
int yyparse (void);
int yyerror (char*);
