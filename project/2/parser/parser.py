from ply import yacc

from scanner import scanner
from parser.ast import Node
from log import logger


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
    if len(p) == 2:
        p[0] = None
        return

    if p[2] is None:
        p[0] = Node('program', args=[p[1]], terminal=False)
    else:
        p[0] = Node('program', args=[p[1], *p[2].args], terminal=False)

def p_decl(p):
    '''
    decl : kind var_list SEMI
    '''
    p[0] = Node('decl', args=[p[1], *p[2].args], terminal=False)

def p_kind(p):
    '''
    kind : int_kw
         | float_kw
    '''
    p[0] = Node(p[1], args=None, terminal=True)

def p_var_list(p):
    '''
    var_list : identifier var_list_prime
    '''
    p[1] = Node(p[1], args=None, attrs={'type': 'identifier'}, terminal=True)
    p[0] = Node('var_list', args=[p[1]], terminal=False)
    if p[2] is not None:
        p[0].args.extend(p[2].args)

def p_var_list_prime(p):
    '''
    var_list_prime : COMMA var_list
                   | empty
    '''
    if len(p) == 2:
        p[0] = None
    else:
        p[0] = p[2]

def p_function_decl(p):
    '''
    function_decl : kind identifier LPAR kind RPAR SEMI
    '''
    p[2] = Node(p[2], args=None, attrs={'type': 'identifier'}, terminal=True)
    p[0] = Node('function_decl', args=[p[1], p[2], p[4]], terminal=False)

def p_function_def(p):
    '''
    function_def : kind identifier LPAR kind identifier RPAR body
    '''
    p[2] = Node(p[2], args=None, attrs={'type': 'identifier'}, terminal=True)
    p[5] = Node(p[5], args=None, attrs={'type': 'identifier'}, terminal=True)
    p[0] = Node('function_def', args=[p[1], p[2], p[4], p[5], p[7]], terminal=False)

def p_body(p):
    '''
    body : LBRACE body_prime RBRACE
    '''
    p[0] = p[2]

def p_body_prime(p):
    '''
    body_prime : decl body_prime
               | stmt body_prime
               | empty
    '''
    if len(p) == 2:
        p[0] = None
    else:
        if p[2] is None:
            p[0] = Node('body', args=[p[1]], terminal=False)
        else:
            p[0] = Node('body', args=[p[1], *p[2].args], terminal=False)

def p_stmt(p):
    '''
    stmt : expr SEMI
         | if_kw LPAR bool_expr RPAR stmt
         | else_kw stmt
         | while_kw LPAR bool_expr RPAR stmt
         | read_kw var_list SEMI
         | write_kw write_expr_list SEMI
         | return_kw expr SEMI
    '''
    # expr
    if len(p) == 3:
        p[0] = p[1]
    else:
        if p[1] == 'if':
            p[0] = Node(p[1], args=[p[3], p[5]], terminal=True)
            # else_stmt
            if p[6] is not None:
                p[0].args.extend(p[6].args)

        elif p[1] == 'else':
            p[0] = Node(p[1], args=[p[2]], terminal=True)

        elif p[1] == 'while':
            p[0] = Node(p[1], args=[p[3], p[5]], terminal=True)

        elif p[1] == 'read':
            p[0] = Node(p[1], args=[p[2]], terminal=True)

        elif p[1] == 'write':
            p[0] = Node(p[1], args=[p[2]], terminal=True)

        else:
            p[1] = Node(p[1], args=[p[2]], terminal=True)

def p_write_expr_list(p):
    '''
    write_expr_list : expr write_expr_list_prime
                    | string write_expr_list_prime
    '''
    # expr
    node = None
    if isinstance(p[1], Node):
        node = p[1]
    else:
        node = Node('write_expr_list', args=[p[1]], terminal=False)

    if p[2] is None:
        p[0] = node
    else:
        p[0] = p[2]
        p[0].args = [p[1], *p[2].args]

def p_write_expr_list_prime(p):
    '''
    write_expr_list_prime : COMMA write_expr_list
                          | empty
    '''
    if len(p) == 2:
        p[0] = None
    else:
        p[0] = p[2]

def p_factor(p):
    '''
    factor : identifier
           | integer_literal
           | float_literal
           | function_call
           | LPAR expr RPAR
    '''
    if len(p) == 2:
        if isinstance(p[1], str):
            p[0] = Node(p[1], args=None, attrs={'type': 'identifier'}, terminal=True)
        elif isinstance(p[1], float):
            p[0] = Node(p[1], args=None, attrs={'type': 'float_literal'}, terminal=True)
        elif isinstance(p[1], int):
            p[0] = Node(p[1], args=None, attrs={'type': 'integer_literal'}, terminal=True)
        else:
            p[0] = p[1]
    else:
        p[0] = p[2]

def p_bool_expr(p):
    '''
    bool_expr : expr boolop expr
    '''
    p[0] = p[2]
    p[0].args = [p[1], p[3]]

def p_function_call(p):
    '''
    function_call : identifier LPAR expr RPAR
    '''
    p[1] = Node(p[1], args=None, attrs={'type': 'identifier'}, terminal=True)
    p[0] = Node('function_call', args=[p[1], p[3]], terminal=False)

def p_term(p):
    '''
    term : uminus term_prime
    '''
    if p[2] is not None:
        p[0] = p[2]
        p[2].args = [p[1], *p[2].args]
    else:
        p[0] = p[1]

def p_term_prime(p):
    '''
    term_prime : mulop term
               | empty
    '''
    if len(p) == 2:
        p[0] = None
    else:
        p[0] = p[1]
        p[0].args = [p[2]]

def p_uminus(p):
    '''
    uminus : MINUS factor %prec uminus
           | factor
    '''
    if p[1] == '-':
        p[0] = Node(p[1], args=[p[2]], terminal=True)
    else:
        p[0] = p[1]

def p_mulop(p):
    '''
    mulop : MULTIPLY
          | DIVIDE
    '''
    p[0] = Node(p[1], args=None, terminal=True)

def p_expr1(p):
    '''
    expr1 : term expr1_prime
    '''
    if p[2] is None:
        p[0] = p[1]
    else:
        p[0] = p[2]
        p[0].args = [p[1], *p[0].args]

def p_expr1_prime(p):
    '''
    expr1_prime : addop expr1
                | empty
    '''
    if len(p) == 2:
        p[0] = None
    else:
        p[0] = p[1]
        p[0].args = [p[2]]

def p_addop(p):
    '''
    addop : PLUS
          | MINUS
    '''
    p[0] = Node(p[1], args=None, terminal=False)

def p_boolop(p):
    '''
    boolop : LT
           | GT
           | EQUAL
           | LE
           | GE
    '''
    p[0] = Node(p[1], args=None, terminal=False)

def p_expr(p):
    '''
    expr : identifier ASSIGN expr
         | expr1
    '''
    if len(p) == 4:
        p[1] = Node(p[1], args=None, attrs={'type': 'identifier'}, terminal=True)
        p[0] = Node(p[2], args=[p[1], p[3]], terminal=False)
    else:
        p[0] = p[1]

def p_empty(p):
    '''
    empty :
    '''
    p[0] = None

def p_error(p):
    if p:
        logger.error(f'Syntax error on line {p.lineno} column {p.lexpos}: {p.type} {p.value}')
        logger.error('Attempting to recover and continue')
        while True:
            token = parser.token()
            if not token or token.type == 'SEMI':
                break

parser = yacc.yacc()
