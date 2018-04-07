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
    if p[1] == None:
        return

    print('name:', p[0])
    if isinstance(p[0], Node):
        print('inside:', p[0])
    p[0] = Node('program', p[1], p[2])

def p_decl(p):
    '''
    decl : kind var_list SEMI
    '''
    print(p)

def p_kind(p):
    '''
    kind : int_kw
         | float_kw
    '''
    # p[0] = Node('kind', )
    print(p)

def p_var_list(p):
    '''
    var_list : identifier var_list_prime
    '''
    print(p)

def p_var_list_prime(p):
    '''
    var_list_prime : COMMA var_list
                   | empty
    '''
    print(p)

def p_function_decl(p):
    '''
    function_decl : kind identifier LPAR kind RPAR SEMI
    '''
    print(p)

def p_function_def(p):
    '''
    function_def : kind identifier LPAR kind identifier RPAR body
    '''
    print(p)

def p_body(p):
    '''
    body : LBRACE body_prime RBRACE
    '''
    print(p)

def p_body_prime(p):
    '''
    body_prime : decl body_prime
               | stmt body_prime
               | empty
    '''
    print(p)

def p_stmt(p):
    '''
    stmt : expr SEMI
         | if_kw LPAR bool_expr RPAR stmt else_stmt
         | while_kw LPAR bool_expr RPAR stmt
         | read_kw var_list SEMI
         | write_kw write_expr_list SEMI
         | return_kw expr SEMI
    '''
    print(p)

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
    print(p)

def p_write_expr_list(p):
    '''
    write_expr_list : expr write_expr_list_prime
                    | string write_expr_list_prime
    '''
    print(p)

def p_write_expr_list_prime(p):
    '''
    write_expr_list_prime : COMMA write_expr_list
                          | empty
    '''

def p_factor(p):
    '''
    factor : identifier
           | integer_literal
           | float_literal
           | function_call
           | LPAR expr RPAR
    '''
    print(p)

def p_bool_expr(p):
    '''
    bool_expr : expr bool_op expr
    '''
    print(p)

def p_function_call(p):
    '''
    function_call : identifier LPAR expr RPAR
    '''
    print(p)

def p_term(p):
    '''
    term : uminus term_prime
    '''
    print(p)

def p_term_prime(p):
    '''
    term_prime : mulop uminus factor term_prime
               | empty
    '''
    print(p)

def p_uminus(p):
    '''
    uminus : MINUS factor %prec uminus
           | factor
    '''
    print(p)

def p_mulop(p):
    '''
    mulop : MULTIPLY
          | DIVIDE
    '''
    p[0] = Node('mulop', p[1], terminal=True)

def p_expr1(p):
    '''
    expr1 : term expr1_prime
    '''
    p[0] = Node('expr1', p[1], p[2], terminal=False)

def p_expr1_prime(p):
    '''
    expr1_prime : add_op expr1
                | empty
    '''
    p[0] = Node('expr1_prime', p[1], p[2], terminal=False)

def p_add_op(p):
    '''
    add_op : PLUS
           | MINUS
    '''
    p[0] = Node('add_op', p[1], terminal=True)

def p_bool_op(p):
    '''
    bool_op : LT
            | GT
            | EQUAL
            | GE
            | LE
    '''
    p[0] = Node('bool_op', p[1], terminal=True)

def p_expr(p):
    '''
    expr : identifier ASSIGN expr
         | expr1
    '''
    print(p)

def p_empty(p):
    '''
    empty :
    '''
    p[0] = None

def p_error(p):
    print(p)

parser = yacc.yacc()
