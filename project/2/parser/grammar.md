```
program : function_def program
        | decl program
        | function_decl program
        | empty

decl : kind var_list SEMI

kind : int_kw
     | float_kw

var_list : var_list_prime identifier 

var_list_prime: var_list COMMA
              | empty

function_decl : kind identifier LPAR kind RPAR SEMI

function_def : kind identifier LPAR kind identifier RPAR body

body : LBRACE body_prime RBRACE

body_prime : decl body_prime
           | stmt body_prime
           | empty

stmt : expr SEMI
     | if_kw LPAR bool_expr RPAR stmt
     | else_kw stmt
     | while_kw LPAR bool_expr RPAR stmt
     | read_kw var_list SEMI
     | write_kw write_expr_list SEMI
     | return_kw expr SEMI

write_expr_list : expr write_expr_list_prime
                | string write_expr_list_prime

write_expr_list_prime : COMMA write_expr_list
                      | empty

factor : identifier
       | integer_literal
       | float_literal
       | function_call
       | LPAR expr RPAR

bool_expr : expr boolop expr

function_call : identifier LPAR expr RPAR

term : term_prime uminus

term_prime : term mulop
           | empty

uminus : MINUS factor
       | factor

mulop : MULTIPLY
      | DIVIDE

expr1 : expr1_prime term

expr1_prime : expr1 addop
            | empty

addop : PLUS
      | MINUS

boolop : LT
       | GT
       | EQUAL
       | LE
       | GE

expr : identifier ASSIGN expr
     | expr1
```
