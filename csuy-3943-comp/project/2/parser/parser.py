from ply import yacc

from scanner import scanner
from parser.ast import Node, OperatorType
import log


class ErrorProduction:
    pass


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
        p[0] = Node('program', args=[p[1]])
    else:
        p[0] = Node('program', args=[p[1], *p[2].args])

def p_decl(p):
    '''
    decl : kind var_list SEMI
    '''
    for var in p[2].args:
        var.attrs['type'] = p[1].symbol

    p[0] = Node(
        'decl',
        args=[*p[2].args],
        attrs={
            'name': 'decl',
            'line': p.lineno(2),
            'type': p[1].symbol,
            'terminal': False
        }
    )

def p_decl_error(p):
    '''
    decl : kind error SEMI
    '''
    log.error(f'decl error on line {p.lineno(2)}')

def p_kind(p):
    '''
    kind : int_kw
         | float_kw
    '''
    if p[1] == 'int':
        p[0] = Node(
            int,
            args=None,
            attrs={
                'name': 'int_kw',
                'type': int,
                'line': p.lineno(1),
                'terminal': True
            }
        )
    else:
        p[0] = Node(
            float,
            args=None,
            attrs={
                'name': 'float_kw',
                'type': float,
                'line': p.lineno(1),
                'terminal': True
            }
        )

def p_var_list(p):
    '''
    var_list : identifier
             | var_list COMMA identifier
    '''
    if len(p) == 2:
        p[1] = Node(
            p[1],
            args=None,
            attrs={
                'name': 'identifier',
                'line': p.lineno(1),
                'terminal': True
            }
        )
        p[0] = Node(
            'var_list',
            args=[p[1]],
            attrs={
                'operator': OperatorType.N_ARY
            }
        )
    else:
        p[0] = p[1]
        p[1].args.append(Node(
            p[3],
            args=None,
            attrs={
                'name': 'identifier',
                'line': p.lineno(3),
                'terminal': True
            }
        ))

def p_function_decl(p):
    '''
    function_decl : kind identifier LPAR kind RPAR SEMI
    '''
    p[2] = Node(
        p[2],
        args=None,
        attrs={
            'type': p[1].symbol,
            'name': 'identifier',
            'line': p.lineno(1),
            'terminal': True
        }
    )
    p[0] = Node(
        'function_decl',
        args=[p[2]],
        attrs={
            'type': p[4].symbol,
            'line': p.lineno(2),
            'operator': OperatorType.UNARY
        }
    )

def p_function_decl_error(p):
    '''
    function_decl : kind identifier LPAR error RPAR SEMI
    '''
    log.error('function_decl error')

def p_function_def(p):
    '''
    function_def : kind identifier LPAR kind identifier RPAR body
    '''
    p[2] = Node(
        p[2],
        args=None,
        attrs={
            'type': p[1].symbol,
            'name': 'identifier',
            'terminal': True
        }
    )
    p[5] = Node(
        p[5],
        args=None,
        attrs={
            'type': p[4].symbol,
            'name': 'identifier',
            'terminal': True
        }
    )
    p[0] = Node(
        'function_def',
        args=[p[2], p[5], p[7]],
        attrs={
            'line': p.lineno(2),
            'operator': OperatorType.TRINARY
        }
    )

def p_function_def_error(p):
    '''
    function_def : kind identifier LPAR kind identifier RPAR error
                 | kind identifier LPAR error RPAR body
    '''
    log.error('function_def error')

def p_body(p):
    '''
    body : LBRACE body_prime RBRACE
    '''
    if p[2] is None:
        p[0] = Node('body', args=[])
    else:
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
        p[0] = Node('body', args=[p[1]])
        if p[2] is not None:
            p[0].args.extend(p[2].args)

def p_stmt(p):
    '''
    stmt : expr SEMI
         | if_kw LPAR bool_expr RPAR stmt else_stmt
         | while_kw LPAR bool_expr RPAR stmt
         | read_kw var_list SEMI
         | write_kw write_expr_list SEMI
         | return_kw expr SEMI
         | LBRACE stmt_prime RBRACE
    '''
    # expr
    if len(p) == 3:
        p[0] = p[1]
    else:
        if p[1] == 'if':
            if p[6] is None:
                p[0] = Node(p[1], args=[p[3], p[5]])
            else:
                p[0] = Node(p[1], args=[p[3], p[5], p[6]])

        elif p[1] == 'while':
            p[0] = Node(
                p[1],
                args=[p[3], p[5]],
                attrs={
                    'name': 'while_kw',
                    'terminal': True,
                    'line': p.lineno(1),
                    'operator': OperatorType.BINARY
                }
            )

        elif p[1] == 'read':
            p[0] = Node(
                p[1],
                args=[*p[2].args],
                attrs={
                    'name': 'read_kw',
                    'terminal': True,
                    'line': p.lineno(1),
                    'operator': OperatorType.N_ARY
                }
            )

        elif p[1] == 'write':
            p[0] = Node(
                p[1],
                args=[*p[2].args],
                attrs={
                    'name': 'write_kw',
                    'terminal': True,
                    'line': p.lineno(1),
                    'operator': OperatorType.N_ARY
                }
            )

        elif p[1] == 'return':
            p[0] = Node(
                p[1],
                args=[p[2]],
                attrs={
                    'name': 'return_kw',
                    'terminal': True,
                    'line': p.lineno(1),
                    'operator': OperatorType.UNARY
                }
            )

        elif p[1] == '{':
            p[0] = p[2]

        else:
            p[0] = p[1]

def p_stmt_error(p):
    '''
    stmt : error
         | error SEMI
    '''
    log.error(f'stmt error on line {p.lineno(1)}')

def p_else_stmt(p):
    '''
    else_stmt : else_kw stmt
              | empty
    '''
    if len(p) == 2:
        p[0] = None
    else:
        p[0] = Node(
            p[1],
            args=[p[2]],
            attrs={
                'name': 'else_kw',
                'terminal': True,
                'line': p.lineno(1)
            }
        )

def p_else_stmt_error(p):
    '''
    else_stmt : error
    '''
    log.error('else_stmt error')

def p_stmt_prime(p):
    '''
    stmt_prime : stmt stmt_prime
               | empty
    '''
    if len(p) == 2:
        p[0] = None
    else:
        if p[2] is None:
            p[0] = p[1]
        else:
            p[0] = Node('stmt_prime', args=[p[1], p[2]])

def p_write_expr_list(p):
    '''
    write_expr_list : expr write_expr_list_prime
                    | string write_expr_list_prime
    '''
    # expr
    if not isinstance(p[1], Node):
        p[1] = Node(
            p[1],
            args=[],
            attrs={
                'name': 'string',
                'terminal': True,
                'line': p.lineno(1)
            }
        )

    node = Node('write_expr_list', args=[p[1]])

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
            p[0] = Node(
                p[1],
                args=None,
                attrs={
                    'name': 'identifier',
                    'line': p.lineno(1),
                    'terminal': True
                }
            )
        elif isinstance(p[1], float):
            p[0] = Node(
                p[1],
                args=None,
                attrs={
                    'name': 'float_literal',
                    'line': p.lineno(1),
                    'terminal': True,
                    'type': float
                }
            )
        elif isinstance(p[1], int):
            p[0] = Node(
                p[1],
                args=None,
                attrs={
                    'name': 'integer_literal',
                    'line': p.lineno(1),
                    'terminal': True,
                    'type': int
                }
            )
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

def p_bool_expr_error(p):
    '''
    bool_expr : error
              | expr error expr
    '''
    log.error(f'bool_expr error on line {p.lineno(1)}')

def p_function_call(p):
    '''
    function_call : identifier LPAR expr RPAR
    '''
    p[1] = Node(p[1], args=None, attrs={
        'name': 'identifier',
        'line': p.lineno(1),
        'terminal': True
    })
    p[0] = Node(
        'function_call',
        args=[p[1], p[3]],
        attrs={
            'line': p.lineno(1),
            'operator': OperatorType.BINARY
        }
    )

def p_term(p):
    '''
    term : uminus
         | term mulop uminus
    '''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = p[2]
        p[0].args = [p[1], p[3]]

def p_uminus(p):
    '''
    uminus : MINUS factor %prec uminus
           | factor
    '''
    if p[1] == '-':
        p[0] = Node(
            p[1],
            args=[p[2]],
            attrs={
                'terminal': True,
                'line': p.lineno(1),
                'operator': OperatorType.UNARY
            }
        )
    else:
        p[0] = p[1]

def p_mulop(p):
    '''
    mulop : DIVIDE
          | MULTIPLY
    '''
    if p[1] == '*':
        p[0] = Node(
            p[1],
            args=None,
            attrs={
                'name': 'MULTIPLY',
                'line': p.lineno(1),
                'terminal': True,
                'operator': OperatorType.BINARY
            }
        )
    else:
        p[0] = Node(
            p[1],
            args=None,
            attrs={
                'name': 'DIVIDE',
                'line': p.lineno(1),
                'terminal': True,
                'operator': OperatorType.BINARY
            }
        )

def p_expr1(p):
    '''
    expr1 : term
          | expr1 addop term
    '''
    if len(p) == 2:
        p[0] = p[1]
    else:
        p[0] = p[2]
        p[0].args = [p[1], p[3]]

def p_expr1_error(p):
    '''
    expr1 : expr1 addop error
    '''
    log.error('expr1 error')

def p_addop(p):
    '''
    addop : PLUS
          | MINUS
    '''
    if p[1] == '+':
        p[0] = Node(
            p[1],
            args=None,
            attrs={
                'name': 'PLUS',
                'line': p.lineno(1),
                'terminal': True,
                'operator': OperatorType.BINARY
            }
        )
    else:
        p[0] = Node(
            p[1],
            args=None,
            attrs={
                'name': 'MINUS',
                'line': p.lineno(1),
                'terminal': True,
                'operator': OperatorType.BINARY
            }
        )

def p_boolop(p):
    '''
    boolop : LT
           | GT
           | EQUAL
           | LE
           | GE
    '''
    name_map = {
        '<': 'LT',
        '>': 'GT',
        '==': 'EQUAL',
        '<=': 'LE',
        '>=': 'GE'
    }
    p[0] = Node(
        p[1],
        args=None,
        attrs={
            'name': name_map[p[1]],
            'line': p.lineno(1),
            'terminal': True,
            'operator': OperatorType.BINARY
        }
    )

def p_expr(p):
    '''
    expr : identifier ASSIGN expr
         | expr1
    '''
    if len(p) == 4:
        p[1] = Node(
            p[1],
            args=None,
            attrs={
                'name': 'identifier',
                'line': p.lineno(1)
            }
        )
        p[0] = Node(
            p[2],
            args=[p[1], p[3]],
            attrs={
                'name': 'ASSIGN',
                'line': p.lineno(1),
                'operator': OperatorType.BINARY
            }
        )
    else:
        p[0] = p[1]

def p_expr_error(p):
    '''
    expr : identifier ASSIGN error
    '''
    log.error('expr error')

def p_empty(p):
    '''
    empty :
    '''
    p[0] = None

def p_error(p):
    if not p:
        log.info('End of file')
        return

    log.error(f'Syntax error on line {p.lineno} position {p.lexpos}: {p.type} {p.value}')
    log.error('Attempting to recover and continue')
    # while True:
        # token = parser.token()
        # if not token or token.type in ('SEMI', 'RBRACE', 'RPAR'):
            # log.error(f'Synchronized on {token}')
            # break
        # log.error(f'Discarding {token}')
    # parser.restart()
    # return token


parser = yacc.yacc()
