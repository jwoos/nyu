from ply import yacc

from scanner import scanner
from parser.ast import Node


tokens = scanner.tokens

precedence = (
    ('right', 'uminus'),
    ('left', 'MULTIPLY', 'DIVIDE'),
    ('left', 'PLUS', 'MINUS'),
    ('right', 'ASSIGN'),
)


def p_program(p):
    '''
    program : function_def program
            | decl program
            | function_decl program
            | empty
    '''
    if p[1] is None:
        p[0] = None
    else:
        p[0] = Node('', args=p[1])

def p_decl(p):
    '''
    decl : kind var_list SEMI
    '''

def p_kind(p):
    '''
    kind : int_kw
         | float_kw
    '''
    p[0] = Node(p[1], args=False, terminal=True)

def p_var_list(p):
    '''
    var_list : identifier var_list_prime
    '''
    p[0] = Node('var_list', p[1], p[2])

def p_var_list_prime(p):
    '''
    var_list_prime : COMMA var_list
                   | empty
    '''
    if len(p) == 3:
        p[0] = p[2]
    else:
        p[0] = p[1]

def p_function_decl(p):
    '''
    function_decl : kind identifier LPAR kind RPAR SEMI
    '''
    p[0] = Node('function_decl', p[0], p[1], p[3])

def p_function_def(p):
    '''
    function_def : kind identifier LPAR kind identifier RPAR body
    '''
    p[0] = Node('function_def', p[0], p[1], p[2], p[4], p[5], p[7])

def p_body(p):
    '''
    body : LBRACE body_prime RBRACE
    '''
    p[0] = Node('body', p[2])

def p_body_prime(p):
    '''
    body_prime : decl body_prime
               | stmt body_prime
               | empty
    '''
    if len(p) == 3:
        p[0] = Node('body_prime', p[1], p[2])
    else:
        p[0] = None

def p_stmt(p):
    '''
    stmt : expr SEMI
         | if_kw LPAR bool_expr RPAR stmt else_stmt
         | while_kw LPAR bool_expr RPAR stmt
         | read_kw var_list SEMI
         | write_kw write_expr_list SEMI
         | return_kw expr SEMI
    '''
    if len(p) == 3:
        pass

# def p_expr_list(p):
#     '''
#     expr_list : expr expr_list_prime
#     '''
#     print(p)
#
# def p_expr_list_prime(p):
#     '''
#     expr_list_prime : COMMA expr
#                     | empty
#     '''
#     print(p)

def p_else_stmt(p):
    '''
    else_stmt : else_kw stmt
              | empty
    '''
    if len(p) == 2:
        p[0] = Node('else_stmt', p[1], p[2])
    else:
        p[0] = None

def p_write_expr_list(p):
    '''
    write_expr_list : expr write_expr_list_prime
                    | string write_expr_list_prime
    '''
    p[0] = Node('write_expr_list')

def p_write_expr_list_prime(p):
    '''
    write_expr_list_prime : COMMA write_expr_list
                          | empty
    '''
    p[0] = Node()

def p_factor(p):
    '''
    factor : identifier
           | integer_literal
           | float_literal
           | function_call
           | LPAR expr RPAR
    '''
    if len(p) == 4:
        p[0] = p[2]
    else:
        p[0] = Node(p[1], terminal=True)

def p_bool_expr(p):
    '''
    bool_expr : expr boolop expr
    '''
    p[0] = Node('bool_expr', p[1], p[2], p[3])

def p_function_call(p):
    '''
    function_call : identifier LPAR expr RPAR
    '''
    p[0] = Node('identifier', p[1], p[2], p[3], p[4])

def p_term(p):
    '''
    term : uminus term_prime
    '''
    p[0] = Node('term', p[1], p[2])

def p_term_prime(p):
    '''
    term_prime : mulop uminus factor term_prime
               | empty
    '''
    if len(p) == 2:
        p[0] = None
    else:
        p[0] = Node('term_prime', p[1], p[2], p[3], p[4])

def p_uminus(p):
    '''
    uminus : MINUS %prec uminus
           | empty
    '''
    if len(p) == 3:
        p[0] = 
    else:

def p_mulop(p):
    '''
    mulop : MULTIPLY
          | DIVIDE
    '''
    p[0] = Node(p[1], args=None, terminal=False)

def p_expr1(p):
    '''
    expr1 : term
          | addop expr1
          | empty
    '''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = Node(p[1], args=[p[0], p[2]], terminal=False)

def p_addop(p):
    '''
    addop : PLUS
          | MINUS
    '''
    p[0] = Node(p[1], args=None, terminal=True)

def p_boolop(p):
    '''
    boolop : LT
           | GT
           | EQUAL
           | GE
           | LE
    '''
    p[0] = Node(p[1], args=None, terminal=False)

def p_expr(p):
    '''
    expr : identifier ASSIGN expr
         | expr1
    '''
    if len(p) == 4:
        p[1] = Node(p[1], args=None, attrs=None, terminal=True)
        p[0] = Node(p[2], args=[p[1], p[3]], attrs=None, terminal=False)
    else:
        p[0] = p[1]

def p_empty(p):
    '''
    empty :
    '''
    p[0] = None

def p_error(p):
    print(p)

parser = yacc.yacc()
