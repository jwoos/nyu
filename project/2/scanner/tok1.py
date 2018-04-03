import ply.lex as lex

#list all the reserved words here, otherwise they will be identified as identifiers (normal words) and not keywords
reserved = {
    'if' : 'if_kw',
    'read':'read_kw',
    'write':'write_kw',
    'else' : 'else_kw',
    'while' : 'while_kw',
    'int':'int_kw',
    'float':'float_kw',
    'return':'return_kw',
}

tokens = [
    'integer_literal',
    'float_literal',
    'identifier',
    'PLUS',
    'MINUS',
    'MULTIPLY',
    'DIVIDE',
    'LPAR',
    'RPAR',
    'LBRACE',
    'RBRACE',
    'SEMI',
    'COMMA',
    'WS',
    'newline',
    'string',
    'EQUAL',
    'comment',
    'ASSIGN',
    'LT',
    'LE',
    'GE',
    'GT'
] + list(reserved.values())

#As defined in table 4
token_dictionary= {
    'int_kw':1,
    'float_kw':2,
    'if_kw':3,
    'else_kw':4,
    'while_kw':5,
    'return_kw':6,
    'read_kw':7,
    'write_kw':8,
    'identifier':10,
    'PLUS':11,
    'MINUS':12,
    'MULTIPLY':14,
    'DIVIDE':15,
    'ASSIGN':16,
    'LPAR':17,
    'RPAR':18,
    'LBRACE':19,
    'RBRACE':20,
    'SEMI':21,
    'COMMA':22,
    'integer_literal':23,
    'float_literal':24,
    'string':25,
    'EQUAL':30,
    'LT':31,
    'LE':32,
    'GT':33,
    'GE':34,
    'newline':99
}

# Regular expression rules for simple tokens
t_PLUS    = r'\+'
t_MINUS   = r'\-'
t_MULTIPLY= r'\*'
t_DIVIDE  = r'/'
t_ASSIGN  = r'\='
t_EQUAL   = r'\=='
t_LPAR    = r'\('
t_RPAR    = r'\)'
t_RBRACE  = r'\}'
t_LBRACE  = r'\{'
t_SEMI    = r'\;'
t_WS      = r' \t'
t_COMMA   = r'\,'
t_GT      = r'\>'
t_GE      = r'\>='
t_LT      = r'\<'
t_LE      = r'\<='

#1.To handle the float tokens: [0-9]*\.?[0-9]
def t_float_literal(t):
    r'[0-9]*\.[0-9]*'
    if(len(str(t.value))>20):
        with open ('TEST_EXHAUSTIVE_OUTPUT','a') as f:
            f.write("Suspiciously large float literal "+ str(t.value) + " in line " + str(t.lineno) + " Replacing by 0\n")
    else:
        t.value = float(t.value)
        return t

#2. To handle the integer tokens:[0-9]+
def t_integer_literal(t):
    r'[0-9]+'
    if(len(str(t.value))>6):
        with open ('TEST_EXHAUSTIVE_OUTPUT','a') as f:
            f.write("Suspiciously large integer literal "+ str(t.value) + " in line " + str(t.lineno) + " Replacing by 0\n")
    else:
        t.value = int(t.value)
        return t

#3. To match the string literals
def t_string(t):
    r'"[^"]+"'
    t.value = t.value[1:-1].replace('\r', '')
    return t

#4. To match the identifiers
def t_identifier(t):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    t.type = reserved.get(t.value,'identifier')    # Check for reserved words
    return t

#5. To match the new_line tokens
def t_newline(t):
    r'\n+'
    t.lexer.lineno += t.value.count("\n")
    # return t

#6. To match the comments
def t_comment(t):
    r'/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*/'
    t.value = str(t.value) + ' is a comment'

# A string containing ignored characters (spaces and tabs)
t_ignore  = ' \t'

# Error handling rule
def t_error(t):
    with open ('TEST_EXHAUSTIVE_OUTPUT','a') as f:
        f.write("Illegal character " + '"'+ str(t.value[0]) + '"' + "\n")
    print "Illegal character '%s'" % t.value[0]
    t.lexer.skip(1)

# Build the lexer
lexer = lex.lex()
