#include <stdlib.h>
#include <stdio.h>
#include "common.h"
#ifdef MSDOS
#include "y_tab.h"
#else
#include "y.tab.h"
#endif
#define MAX_CODE 1000
#define MAX_LABELS 100
#define MAX_MEMORY 10001
#define STACK_SIZE 1000
#define NO_CODES 39 /* !!! */
#define SET_FORMAT(op,num,x,y,z) \
{\
  format[op-ADD].operands=num;\
  format[op-ADD].op1=x;\
  format[op-ADD].op2=y;\
  format[op-ADD].op3=z;\
}

thing DUMMY = { NONE };
int start= -1;
int no_labels=0;
int icount=0;

struct 
{
  int operands, op1, op2, op3;
} format [NO_CODES];

struct 
{
  int opcode;
  thing op1, op2, op3;
} code [MAX_CODE];

union WORD { int INT; float FLT; } Memory[MAX_MEMORY], Stack[STACK_SIZE];
int top=0;

struct 
{
  int name,place;
} labels [MAX_LABELS];

void push (x, where)
     int x, where;
{
  if (top >= STACK_SIZE)
    {
      fprintf(stderr,"Stack overflow in instruction #%d.",where);
      exit(1);
    }
  else Stack[top++].INT=x;
}

void pushf (x, where)
     float x; int where;
{
  if (top >= STACK_SIZE)
    {
      fprintf(stderr,"Stack overflow in instruction #%d.",where);
      exit(1);
    }
  else Stack[top++].FLT=x;
}

union WORD pop(int where)
{
  if (top <= 0)
    {
      fprintf(stderr,"Stack underflow in instruction #%d.",where);
      exit(1);
    }
  else return Stack[--top];
}
  
int memory_check(x)
     int x;
{
  if (x<0)
    {
      fprintf(stderr,"Negative addresses not allowed\n.");
      fprintf(stderr,"Tried to reference data address %d.\n.",x);
      exit(1);
    }
  if (x>=MAX_MEMORY)
    {
      fprintf(stderr,"Implementation restriction: Data memory restricted to 0 ... %d.\n", MAX_MEMORY-1);
      fprintf(stderr,"Tried to reference data address %d.\n.",x);
      exit(1);
    }
  return x;
}

void code_memory_check(x)
     int x;
{
  if (x<0)
    {
      fprintf(stderr,"Negative addresses not allowed\n.");
      fprintf(stderr,"Tried to reference code address %d.\n.",x);
      exit(1);
    }
  if (x>=MAX_CODE)
    {
      fprintf(stderr,"Implementation restriction: Program memory restricted to 0 ... %d.\n", MAX_CODE-1);
      fprintf(stderr,"Tried to reference code address %d.\n.",x);
      exit(1);
    }
}

int find(int);
  
void init_format()
{
  SET_FORMAT(ADD,3,SRC,SRC,TARGET);
  SET_FORMAT(ADDF,3,SRCF,SRCF,TARGET);
  SET_FORMAT(SUB,3,SRC,SRC,TARGET);
  SET_FORMAT(SUBF,3,SRCF,SRCF,TARGET);
  SET_FORMAT(MUL,3,SRC,SRC,TARGET);
  SET_FORMAT(MULF,3,SRCF,SRCF,TARGET);
  SET_FORMAT(DIV,3,SRC,SRC,TARGET);
  SET_FORMAT(DIVF,3,SRCF,SRCF,TARGET);
  SET_FORMAT(JEQ,3,SRC,SRC,LBL);
  SET_FORMAT(JEQF,3,SRCF,SRCF,LBL);
  SET_FORMAT(JNE,3,SRC,SRC,LBL);
  SET_FORMAT(JNEF,3,SRCF,SRCF,LBL);
  SET_FORMAT(JLE,3,SRC,SRC,LBL);
  SET_FORMAT(JLEF,3,SRCF,SRCF,LBL);
  SET_FORMAT(JLT,3,SRC,SRC,LBL);
  SET_FORMAT(JLTF,3,SRCF,SRCF,LBL);
  SET_FORMAT(JGE,3,SRC,SRC,LBL);
  SET_FORMAT(JGEF,3,SRCF,SRCF,LBL);
  SET_FORMAT(JGT,3,SRC,SRC,LBL);
  SET_FORMAT(JGTF,3,SRCF,SRCF,LBL);
  SET_FORMAT(LABEL,1,LBL,NONE,NONE);
  SET_FORMAT(JUMP,1,LBL,NONE,NONE);
  SET_FORMAT(CALL,1,(LBL|SYMB),NONE,NONE);
  SET_FORMAT(NEG,2,SRC,TARGET,NONE);
  SET_FORMAT(NEGF,2,SRCF,TARGET,NONE);
  SET_FORMAT(COPY,2,SRC,TARGET,NONE);
  SET_FORMAT(COPYF,2,SRCF,TARGET,NONE);
  SET_FORMAT(RETURN,0,NONE,NONE,NONE);
  SET_FORMAT(READ,1,TARGET,NONE,NONE);
  SET_FORMAT(READF,1,TARGET,NONE,NONE);
  SET_FORMAT(WRITE,1,SRC,NONE,NONE);
  SET_FORMAT(WRITEF,1,SRCF,NONE,NONE);
  SET_FORMAT(WRITES,1,STR,NONE,NONE);
  SET_FORMAT(NEWLINE,0,NONE,NONE,NONE);
  SET_FORMAT(STOP,0,NONE,NONE,NONE);
  SET_FORMAT(START,1,LBL,NONE,NONE);
  SET_FORMAT(PUSH,1,SRC,NONE,NONE);
  SET_FORMAT(PUSHF,1,SRCF,NONE,NONE);
  SET_FORMAT(POP,1,TARGET,NONE,NONE);
}


void insert(num,operation,op1,op2,op3)
     int num, operation;
     thing op1, op2, op3;
{
  if (format[operation].operands != num)
    {
      fprintf (stderr, 
	       "Wrong number of arguments to %s in line %d. Ignoring the line.\n",
	       op_name,
	       line_no);
    }
  else if (((num<3) || (op3.kind & format[operation].op3)) &&
	   ((num<2) || (op2.kind & format[operation].op2)) &&
	   ((num<1) || (op1.kind & format[operation].op1)))
      /* Perfect. OK to insert. */
    switch(operation+ADD)
      {
      case START:
	if (start >= 0) /* Already have one START */
	  fprintf(stderr,"Multiple START commands. Ignoring.\n");
	else start = op1.u.value;
	break;
	  
      case LABEL:
	{
	  int i;
	    
	  for (i=0; i<no_labels; i++)
	    if (labels[i].name==op1.u.value) break;
	  
	  if (i<no_labels)
	    fprintf(stderr,
		    "Duplicate definition for label %d in line %d.\n",
		    op1.u.value,
		    line_no);
	  else 
	    {
	      labels[no_labels].name = op1.u.value;
	      labels[no_labels].place = icount;
	      no_labels++;
	      if (no_labels == MAX_LABELS)
		{
		  fprintf(stderr,"Too many labels. Giving up.\n");
		  exit(1);
		}
	    }
	};
	break; 
	
      default: 
	code[icount].opcode = operation+ADD;
	code[icount].op1 = op1;
	code[icount].op2 = op2;
	code[icount].op3 = op3;
	icount++;
      }
  else 
    {
      fprintf(stderr,
	      "Wrong type of an argument to %s in line %d.\n",
	      op_name,
	      line_no);
    }
}

void fix_up()
{
  int i;
  
  for (i=0; i<icount; i++)
    {
      int adj_opcode = code[i].opcode-ADD;
      
      /* IMPORTANT: do not use `kind' of input, but that of format table. */
      if ((format[adj_opcode].op1 & LBL)& (code[i].op1.kind != SYMB))
	{
	  code[i].op1.kind = ADDR;
	  code[i].op1.u.value = find(code[i].op1.u.value);
	}
      else if ((code[i].op1.kind==ADDR)||(code[i].op1.kind==INDIRECT))
	code_memory_check(code[i].op1.u.value);
      	  
      if ((format[adj_opcode].op2 & LBL)& (code[i].op2.kind != SYMB))
	{
	  code[i].op2.kind = ADDR;
	  code[i].op2.u.value = find(code[i].op2.u.value);
	}
      else if ((code[i].op2.kind==ADDR)||(code[i].op2.kind==INDIRECT))
	code_memory_check(code[i].op2.u.value);

      if ((format[adj_opcode].op3 & LBL)& (code[i].op3.kind != SYMB))
	{
	  code[i].op3.kind = ADDR;
	  code[i].op3.u.value = find(code[i].op3.u.value);
	}
      else if ((code[i].op3.kind==ADDR)||(code[i].op3.kind==INDIRECT))
	code_memory_check(code[i].op3.u.value);
    }

  if (start<0)
    {
      fprintf(stderr,"Did not find the START instruction. Giving up.\n");
      exit(1);
    }
  
  start=find(start);

  if (start==icount)
    {
      fprintf(stderr,"Start beyond the end of program!?!?\n");
      exit(1);
    }

}

int find(label)
     int label;
{
  int i;
  for (i=0;i<no_labels; i++)
    if (labels[i].name==label)
      if ((labels[i].place < 0 )|| (labels[i].place >= icount))
	{
	  fprintf(stderr,
		  "Label %d points outside the program. How can it be?\n",
		  label);
	  return icount;
	}
      else return labels[i].place;
    else ;

  /* Get here only if could not find the label. */
  fprintf(stderr,
	  "Label %d not found.\n", label);
	  return 0;
}  

#define VAL(x) code[IC].x.u.value
#define VALF(x) code[IC].x.u.valuef
#define KIND(x) code[IC].x.kind
#define MEM(x) Memory[VAL(x)].INT
#define MEMF(x) Memory[VAL(x)].FLT
#define TO(x)  code[IC].x.u.value
#define FROM(x) ((KIND(x)==CONST) ? VAL(x) : ((KIND(x)==ADDR) ? MEM(x) : Memory[memory_check(MEM(x))].INT))
#define FROMF(x) ((KIND(x)==CONSTF) ? VALF(x) : ((KIND(x)==CONST) ? (float) VAL(x) : ((KIND(x)==ADDR) ? MEMF(x) : Memory[memory_check(MEM(x))].FLT)))
#define DEST(x) Memory[(KIND(x)==ADDR) ? VAL(x) : Memory[memory_check(VAL(x))].INT].INT
#define DESTF(x) Memory[(KIND(x)==ADDR) ? VAL(x) : Memory[memory_check(VAL(x))].INT].FLT
#define STRRING(x) code[IC].x.u.ptr

void run(IC) 
     int IC;
{
  extern double exp(double), log(double), sqrt(double);
  
again:   
  while (1)
    { 
      if (IC >=icount)
	{
	  fprintf(stderr,"Fell off the end of the program without encountering a STOP!!!\n");
	  exit(1);
	}

      switch(code[IC].opcode)
      {  
      case ADD:
	DEST(op3) = FROM(op1) + FROM(op2); break;
		
      case ADDF:
	DESTF(op3) = FROMF(op1) + FROMF(op2); break;
		
      case SUB:
	DEST(op3) = FROM(op1) - FROM(op2); break;
		
      case SUBF:
	DESTF(op3) = FROMF(op1) - FROMF(op2); break;
		
      case DIV:
	if (FROM(op2)==0)
	  {
	    fprintf(stderr, "Divide by 0. Bailing out.\n");
	    exit(2);
	  }
	else DEST(op3) = FROM(op1) / FROM(op2); break;
		
      case DIVF:
	if (FROMF(op2)==0)
	  {
	    fprintf(stderr, "Floating divide by 0. Bailing out.\n");
	    exit(2);
	  }
	else DESTF(op3) = FROMF(op1) / FROMF(op2); break;
		
      case MUL:
	DEST(op3) = FROM(op1) * FROM(op2); break;
		
      case MULF:
	DESTF(op3) = FROMF(op1) * FROMF(op2); break;
		
      case JUMP:
	IC = TO(op1); goto again;
		
      case JLE:
	if (FROM(op1) <= FROM(op2)) { IC = TO(op3); goto again;} else break;
	
      case JLEF:
	if (FROMF(op1) <= FROMF(op2)) { IC = TO(op3); goto again;} else break;
	
      case JNE:
	if (FROM(op1) != FROM(op2)) { IC = TO(op3); goto again;} else break;
	
      case JNEF:
	if (FROMF(op1) != FROMF(op2)) { IC = TO(op3); goto again;} else break;
	
      case JLT:
	if (FROM(op1) < FROM(op2)) { IC = TO(op3); goto again;} else break;
	
      case JLTF:
	if (FROMF(op1) < FROMF(op2)) { IC = TO(op3); goto again;} else break;
	
      case JGE:
	if (FROM(op1) >= FROM(op2)) { IC = TO(op3); goto again;} else break;
	
      case JGEF:
	if (FROMF(op1) >= FROMF(op2)) { IC = TO(op3); goto again;} else break;
	
      case JGT:
	if (FROM(op1) > FROM(op2)) { IC = TO(op3); goto again;} else break;
	
      case JGTF:
	if (FROMF(op1) > FROMF(op2)) { IC = TO(op3); goto again;} else break;
	
      case JEQ:
	if (FROM(op1) == FROM(op2)) { IC = TO(op3); goto again;} else break;
	
      case JEQF:
	if (FROMF(op1) == FROMF(op2)) { IC = TO(op3); goto again;} else break;
	
      case NEG:
	DEST(op2) = -FROM(op1); break;
		
      case NEGF:
	DESTF(op2) = -FROMF(op1); break;
		
      case COPY:
	DEST(op2) = FROM(op1); break;
		
      case COPYF:
	DESTF(op2) = FROMF(op1); break;
		
      case READ:
	printf("Type an integer, please> ");
	scanf(" %d", &DEST(op1)); break;

      case READF:
	printf("Type a floating point number, please> ");
	scanf(" %g", &DESTF(op1)); break;

      case WRITE:
	printf(" %d", FROM(op1)); break;
			
      case WRITEF:
	printf(" %g", FROMF(op1)); break;
			
      case WRITES:
	printf("%s", STRRING(op1)); break;
			
      case NEWLINE:
	putchar('\n'); break;
			
      case STOP:
	printf("Execution completed.\n\n\t\tHave a nice day.\n"); exit(0);

      case LABEL:
      case START:
	fprintf(stderr,"You are entering the twilight zone. This can't be happenning.\n");
	exit(3);

      case CALL:
	switch(KIND(op1))
	  {
	  case ADDR:
	    run(TO(op1)); break;
	  case SYMB:
	    switch(TO(op1))
	      {
	      case FN_SQRT:
		pushf((float)sqrt((double)pop(IC).FLT),IC); break;
	      case FN_LOG:
		pushf((float)log((double)pop(IC).FLT),IC); break;
	      case FN_EXP:
		pushf((float)exp((double)pop(IC).FLT),IC); break;
	      default:
		fprintf(stderr,"Impossible function in CALL. This can't be happenning.\n");
		exit(4);
	      }
	    break;
	  default:
	    fprintf(stderr,"Impossible argument in CALL. This can't be happenning.\n");
	    exit(5);
	  }
	break;

      case RETURN:
	return;

      case PUSH:
	push(FROM(op1),IC); break;
		
      case PUSHF:
	pushf(FROMF(op1),IC); break;
		
      case POP: /* UGLY KLUDGE !! Need something less specific than DEST or DESTF */
	Memory[(KIND(op1)==ADDR) ? VAL(op1) : Memory[memory_check(VAL(op1))].INT]=pop(IC); break;
	
      default:
	fprintf(stderr,"Illegal opcode %d at run time?\n", code[IC].opcode);
	exit(1);
	
      }
      IC++;
    }
}
