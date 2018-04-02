extern int line_no;
extern char op_name[20];

#define YYSTYPE token_type

/* was
typedef struct
  {
    int kind;
    union {int value; float valuef; char *ptr;} u;
  } thing;
*/

typedef union {
  int value;
  float valuef;
  char *ptr;
} token_type;

      
extern YYSTYPE yylval;

/* extern thing DUMMY; */

int yylex (void);
int yyparse (void);
int yyerror (char*);

/* Tokens */
#define KW_INT 1
#define KW_FLOAT 2
#define KW_IF 3
#define KW_ELSE 4
#define KW_WHILE 5
#define KW_RETURN 6
#define KW_READ 7
#define KW_WRITE 8
#define ID 10
#define OP_PLUS 11
#define OP_MINUS 12
#define OP_MULT 14
#define OP_DIV 15
#define OP_ASSIGN 16
#define OP_EQ 30
#define OP_LT 31
#define OP_LE 32
#define OP_GT 33
#define OP_GE 34
#define LPAR 17
#define RPAR 18
#define LBRACE 19
#define RBRACE 20
#define SEMICOLON 21
#define COMMA 22
#define INT_LIT 23
#define FLOAT_LIT 24
#define STRING_LIT 25

/* not really tokens */
#define NL_TOKEN 100
#define WS_TOKEN 99
