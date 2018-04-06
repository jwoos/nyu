from ply import yacc

from scanner import scanner


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
    pass

def p_decl(p):
    '''
    decl : kind var_list SEMI
    '''
    pass

def p_kind(p):
    '''
    kind : int_kw
         | float_kw
    '''
    pass

def p_var_list(p):
    '''
    var_list : identifier var_list_prime
    '''
    pass

def p_var_list_prime(p):
    '''
    var_list_prime : COMMA var_list
                   | empty
    '''
    pass

def p_function_decl(p):
    '''
    function_decl : kind identifier LPAR kind RPAR SEMI
    '''
    pass

def p_function_def(p):
    '''
    function_def : kind identifier LPAR kind identifier RPAR body
    '''
    pass

def p_body(p):
    '''
    body : LBRACE body_prime RBRACE
    '''
    pass

def p_body_prime(p):
    '''
    body_prime : decl body_prime
               | stmt body_prime
               | empty
    '''
    pass

def p_stmt(p):
    '''
    stmt : expr SEMI
         | if_kw LPAR expr RPAR stmt else_stmt
         | while_kw LPAR bool_expr RPAR stmt
         | read_kw var_list SEMI
         | write_kw write_expr_list SEMI
         | return_kw expr SEMI
    '''
    pass

# def p_expr_list(p):
#     '''
#     expr_list : expr expr_list_prime
#     '''
#     pass
#
# def p_expr_list_prime(p):
#     '''
#     expr_list_prime : COMMA expr
#                     | empty
#     '''
#     pass

def p_else_stmt(p):
    '''
    else_stmt : else_kw stmt
              | empty
    '''
    pass

def p_write_expr_list(p):
    '''
    write_expr_list : expr write_expr_list_prime
                    | string write_expr_list_prime
    '''
    pass

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
    pass

def p_bool_expr(p):
    '''
    bool_expr : expr bool_op expr
    '''
    pass

def p_function_call(p):
    '''
    function_call : identifier LPAR expr RPAR
    '''
    pass

def p_term(p):
    '''
    term : uminus term_prime
    '''
    pass

def p_term_prime(p):
    '''
    term_prime : mulop uminus factor term_prime
               | empty
    '''
    pass

def p_uminus(p):
    '''
    uminus : MINUS factor %prec uminus
           | factor
    '''
    pass

def p_mulop(p):
    '''
    mulop : MULTIPLY
          | DIVIDE
    '''
    pass

def p_expr1(p):
    '''
    expr1 : term expr1_prime
    '''
    pass

def p_expr1_prime(p):
    '''
    expr1_prime : add_op expr1
                | empty
    '''
    pass

def p_add_op(p):
    '''
    add_op : PLUS
           | MINUS
    '''
    pass

def p_bool_op(p):
    '''
    bool_op : LT
            | GT
            | EQUAL
            | GE
            | LE
    '''
    pass

def p_expr(p):
    '''
    expr : identifier ASSIGN expr SEMI
         | expr1 SEMI
    '''
    pass

def p_empty(p):
    '''
    empty :
    '''
    pass

def p_error(p):
    print(p)

parser = yacc.yacc()
