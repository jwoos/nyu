from code.asm import ASM
from code.memory import Stack, Memory, Label, Function, new_memory, new_label
from parser.ast import Node
from semantics.symbol_table import SymbolType, Symbol, SymbolScope


NUMERICAL_OPERATION = {'+', '-', '=', '*', '/'}
BOOLEAN_OPERATION = {'<=', '>=', '==', '<', '>'}
KNOWN = {'identifier', 'integer_literal', 'float_literal'}


def generate(ast, table_cache, global_table):
    output = []
    stack = Stack()
    node_stack = [ast]
    table_stack = [global_table]

    table = None

    # initialize globals
    generate_memory(table_stack[0], False)

    while node_stack:
        node = node_stack.pop()

        if node.symbol == 'function_def':
            output.append(generate_function(stack, node_stack, table_stack, table_cache, node))
            continue

        for child in reversed(node.args):
            if child:
                node_stack.append(child)

    output.append(ASM('START', table_stack[0].get('main').get('label')))

    return output

# everything can be dealt with in here since only functions
# can have any operations or calls
def generate_function(stack, node_stack, table_stack, table_cache, function):
    function_identifier = function.args[0]
    function_argument = function.args[1]
    function_body = function.args[2]

    table_stack.append(table_cache[function_identifier.symbol])

    node_stack.append(Node(
        'function_def_end',
        args=[function_identifier],
        attrs={}
    ))
    node_stack.append(function_body)

    output = []
    # generate local variables
    generate_memory(table_stack[-1], True)
    function_symbol = table_stack[0].get(function.args[0].symbol)

    # function is not main
    if function_identifier.symbol != 'main':
        output.append(ASM('POP', function_argument.get('memory')))

    output.append(ASM('LABEL', function_symbol.attrs['label']))

    while node_stack:
        node = node_stack.pop()

        if node.symbol == 'return' or node.symbol == 'function_def_end':
            if node.symbol == 'return':
                output.append(ASM('PUSH', table_stack[-1].get(Symbol.RETURN_KEY).get('memory')))

            table_stack.pop()

            if function_identifier.symbol == 'main':
                # if main then just exit the program since we're at the end
                output.append(ASM('STOP'))
            else:
                # TODO needs return values
                # if another function then let's return
                output.append(ASM('RETURN'))

            # exit the loop - we're done working on the function
            return output

        elif node.symbol == 'write':
            for arg in node.args:
                if arg.get('name') == 'string':
                    output.append(ASM('WRITES', ASM.string(arg.symbol)))
                elif arg.get('name') == 'integer_literal':
                    output.append(ASM('WRITE', ASM.literal(arg.symbol)))
                elif arg.get('name') == 'float_literal':
                    output.append(ASM('WRITEF', ASM.literal(arg.symbol)))
                elif arg.get('name') == 'identifier':
                    identifier_symbol = table_stack[-1].get(arg.symbol) or table_stack[0].get(arg.symbol)

                    if identifier_symbol.get('type') == int:
                        output.append(ASM('WRITE', identifier_symbol.get('memory')))
                    else:
                        output.append(ASM('WRITEF', identifier_symbol.get('memory')))
                else:
                    # TODO deal with expressions
                    # this is an expression
                    output.append(generate_expr(table_stack, arg))
                    output.append(ASM(
                        ASM.wrap_type('WRITE', arg.get('type')),
                        table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')
                    ))

                # there should be a space between all the items being written
                output.append(ASM('WRITES', ASM.string(' ')))

            # newline after writing is done
            output.append(ASM('NEWLINE'))

            continue

        elif node.symbol == 'read':
            for arg in node.args:
                if arg.get('name') == 'identifier':
                    identifier_symbol = table_stack[-1].get(arg.symbol) or table_stack[0].get(arg.symbol)

                    if identifier_symbol.get('type') == int:
                        output.append(ASM('READ', identifier_symbol.get('memory')))
                    else:
                        output.append(ASM('READF', identifier_symbol.get('memory')))

            continue

        elif node.symbol == 'function_call':
            pass

        elif node.symbol == '=':
            output.append(generate_expr(table_stack, node))

        else:
            print('what is dis', node)

        for child in reversed(node.args):
            if child:
                node_stack.append(child)

def generate_function_call(stack, node_stack, table_stack, node):
    pass

def generate_expr(table_stack, node):
    output = []

    left = node.args[0]
    right = node.args[1]

    # deal with left side
    if left.get('name') in KNOWN:
        if left.get('name') == 'identifier':
            left_symbol = table_stack[-1].get(left.symbol) or table_stack[0].get(left.symbol)
            left_arg = left_symbol.get('memory')
        else:
            left_arg = ASM.constant(left.symbol)
    else:
        output.append(generate_expr(table_stack, left))

        # copy the resulting value into temp left
        output.append(ASM(
            'COPY',
            table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory'),
            table_stack[-1].get(Symbol.TEMP_A_KEY).get('memory')
        ))
        table_stack[-1].get(Symbol.TEMP_A_KEY).set('type', table_stack[-1].get(Symbol.TEMP_C_KEY).get('type'))

        left_arg = table_stack[-1].get(Symbol.TEMP_A_KEY).get('memory')

    # deal with right side
    if right.get('name') in KNOWN:
        if right.get('name') == 'identifier':
            right_symbol = table_stack[-1].get(right.symbol) or table_stack[0].get(right.symbol)
            right_arg = right_symbol.get('memory')
        else:
            right_arg = ASM.constant(right.symbol)
    else:
        output.append(generate_expr(table_stack, right))

        # copy the resulting value into temp right
        output.append(ASM(
            'COPY',
            table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory'),
            table_stack[-1].get(Symbol.TEMP_B_KEY).get('memory')
        ))
        table_stack[-1].get(Symbol.TEMP_B_KEY).set('type', table_stack[-1].get(Symbol.TEMP_C_KEY).get('type'))

        right_arg = table_stack[-1].get(Symbol.TEMP_B_KEY).get('memory')

    if node.symbol == '=':
        output.append(ASM(
            'COPY',
            right_arg,
            left_arg
        ))

        output.append(ASM(
            'COPY',
            left_arg,
            table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')
        ))
        table_stack[-1].get(Symbol.TEMP_C_KEY).set('type', node.get('type'))
    else:
        output.append(ASM(
            ASM.wrap_type(ASM.NUMERICAL_OPERATION_MAP[node.symbol], node.get('type')),
            left_arg,
            right_arg,
            table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')
        ))
        table_stack[-1].get(Symbol.TEMP_C_KEY).set('type', node.get('type'))

    return output

def generate_memory(table, is_function):
    # generate variables for a given table
    for k, v in table.items():
        if v.kind == SymbolType.VARIABLE:
            v.attrs['memory'] = new_memory()
        else:
            v.attrs['label'] = new_label()

    # generate a return address
    if is_function:
        table.set(Symbol.RETURN_KEY, Symbol(SymbolScope.LOCAL, SymbolType.OTHER, attrs={'memory': new_memory()}))
        table.set(Symbol.TEMP_A_KEY, Symbol(SymbolScope.LOCAL, SymbolType.OTHER, attrs={'memory': new_memory()}))
        table.set(Symbol.TEMP_B_KEY, Symbol(SymbolScope.LOCAL, SymbolType.OTHER, attrs={'memory': new_memory()}))
        table.set(Symbol.TEMP_C_KEY, Symbol(SymbolScope.LOCAL, SymbolType.OTHER, attrs={'memory': new_memory()}))
