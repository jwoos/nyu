from code.asm import ASM
from code.memory import new_memory, new_label
from parser.ast import Node
from semantics.symbol_table import SymbolType, Symbol, SymbolScope
import log


NUMERICAL_OPERATION = {'+', '-', '=', '*', '/'}
BOOLEAN_OPERATION = {'<=', '>=', '==', '<', '>'}
KNOWN = {'identifier', 'integer_literal', 'float_literal'}


def generate(ast, table_cache, global_table):
    output = []
    node_stack = [ast]
    table_stack = [global_table]

    table = None

    # initialize globals
    generate_memory(table_stack[0], False)

    while node_stack:
        node = node_stack.pop()

        if node.symbol == 'function_def':
            output.append(generate_function(node_stack, table_stack, table_cache, node))
            continue

        for child in reversed(node.args):
            if child:
                node_stack.append(child)

    output.append(ASM('START', table_stack[0].get('main').get('label')))

    return output

# everything can be dealt with in here since only functions
# can have any operations or calls
def generate_function(node_stack, table_stack, table_cache, function):
    function_identifier = function.args[0]
    function_argument = function.args[1]
    function_body = function.args[2]

    table_stack.append(table_cache[function_identifier.symbol])

    node_stack.append(Node(
        'function_def_end',
        args=[function_identifier],
        attrs={}
    ))

    output = []
    # generate local variables
    generate_memory(table_stack[-1], True)
    function_symbol = table_stack[0].get(function.args[0].symbol)

    output.append(ASM('LABEL', function_symbol.attrs['label']))

    # function is not main
    if function_identifier.symbol != 'main':
        output.append(ASM('POP', table_stack[-1].get(function_argument.symbol).get('memory')))

    output.append(generate_body(table_stack, function_body))

    if table_stack[-1].name == 'main':
        # if main then just exit the program since we're at the end
        output.append(ASM('STOP'))
    else:
        # if another function then let's return
        output.append(ASM('RETURN'))

    table_stack.pop()

    return output

# deal with function bodies as well as bodies of conditionals
def generate_body(table_stack, body):
    node_stack = [body]
    output = []

    while node_stack:
        node = node_stack.pop()

        if node.symbol == 'return':
            if node.args[0].get('name') in KNOWN:
                if node.args[0].get('name') == 'identifier':
                    symbol = table_stack[-1].get(node.args[0].symbol) or table_stack[0].get(node.args[0].symbol)
                    arg = symbol.get('memory')
                else:
                    arg = ASM.constant(node.args[0].symbol)
            else:
                output.append(generate_expr(table_stack, node.args[0]))
                output.append(ASM('POP', table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')))
                arg = table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')

            output.append(ASM('PUSH', arg))

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
                    # this is an expression
                    output.append(generate_expr(table_stack, arg))
                    output.append(ASM('POP', table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')))
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
            output.append(generate_function_call(table_stack, node))

            continue

        elif node.symbol in NUMERICAL_OPERATION:
            output.append(generate_expr(table_stack, node))
            output.append(ASM('POP', table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')))

            continue

        elif node.symbol == 'if':
            output.append(generate_if(table_stack, node))

            continue

        elif node.symbol == 'while':
            output.append(generate_while(table_stack, node))

            continue

        else:
            # all nodes here can be ignored
            pass

        for child in reversed(node.args):
            if child:
                node_stack.append(child)

    return output

def generate_function_call(table_stack, node):
    output = []
    function_symbol = table_stack[0].get(node.args[0].symbol)

    table_items = tuple(table_stack[-1].items())

    # push all locals onto stack
    for identifier, symbol in table_items:
        if identifier[0] == '<':
            continue

        output.append(ASM(
            ASM.wrap_type('PUSH', symbol.get('type')),
            symbol.get('memory')
        ))

    # get the argument
    if node.args[1].get('name') in KNOWN:
        if node.args[1].get('name') == 'identifier':
            symbol = table_stack[-1].get(node.args[1].symbol) or table_stack[0].get(node.args[1].symbol)
            arg = symbol.get('memory')
        else:
            arg = ASM.constant(node.args[1].symbol)

        output.append(ASM(
            ASM.wrap_type('COPY', node.args[1].get('type') or symbol.get('type')),
            arg,
            table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')
        ))
        table_stack[-1].get(Symbol.TEMP_C_KEY).set('type',  node.args[1].get('type') or symbol.get('type'))

    else:
        output.append(generate_expr(table_stack, node.args[1]))
        output.append(ASM('POP', table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')))

    output.append(ASM(
        ASM.wrap_type('PUSH', node.args[1].get('type')),
        table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')
    ))

    output.append(ASM('CALL', function_symbol.get('label')))

    output.append(ASM('POP', table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')))

    for identifier, symbol in reversed(table_items):
        if identifier[0] == '<':
            continue

        output.append(ASM(
            'POP',
            symbol.get('memory')
        ))

    return output

def generate_expr(table_stack, node):
    output = []

    if len(node.args) == 0:
        # base case
        if node.get('name') in KNOWN:
            if node.get('name') == 'identifier':
                symbol = table_stack[-1].get(node.symbol) or table_stack[0].get(node.symbol)
                arg = symbol.get('memory')
            else:
                arg = ASM.constant(node.symbol)

            output.append(ASM(
                ASM.wrap_type('PUSH', node.get('type')),
                arg
            ))

        else:
            # TODO figure out if this can be removed
            # output.append(generate_expr(table_stack, node.args[0]))
            log.warning('should not be here generate_expr')

        return output

    elif len(node.args) == 1:
        if node.symbol == '-':
            output.append(generate_expr(table_stack, node.args[0]))

            output.append(ASM(
                'POP',
                table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')
            ))
            # deal with unary minus
            output.append(ASM(
                ASM.wrap_type('NEG', node.get('type')),
                table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory'),
                table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')
            ))
            table_stack[-1].get(Symbol.TEMP_C_KEY).set('type', node.get('type'))

            output.append(ASM(
                ASM.wrap_type('PUSH', node.get('type')),
                table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')
            ))

        else:
            # TODO figure out if this can be removed
            # output.append(generate_expr(table_stack, node.args[0]))
            log.warning('should not be here generate_expr')

        return output

    elif node.symbol == 'function_call':
        # deal with a function call
        output.append(generate_function_call(table_stack, node))
        table_stack[-1].get(Symbol.TEMP_C_KEY).set('type', node.get('type'))

        output.append(ASM(
            ASM.wrap_type('PUSH', node.get('type')),
            table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')
        ))

        return output

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

    # deal with right side
    if right.get('name') in KNOWN:
        if right.get('name') == 'identifier':
            right_symbol = table_stack[-1].get(right.symbol) or table_stack[0].get(right.symbol)
            right_arg = right_symbol.get('memory')
        else:
            right_arg = ASM.constant(right.symbol)
    else:
        output.append(generate_expr(table_stack, right))

    # popping has to be done backwards
    if right.get('name') not in KNOWN:
        # copy the resulting value into temp right
        output.append(ASM(
            'POP',
            table_stack[-1].get(Symbol.TEMP_B_KEY).get('memory')
        ))
        table_stack[-1].get(Symbol.TEMP_B_KEY).set('type', table_stack[-1].get(Symbol.TEMP_C_KEY).get('type'))

        right_arg = table_stack[-1].get(Symbol.TEMP_B_KEY).get('memory')

    if left.get('name') not in KNOWN:
        # copy the resulting value into temp left
        output.append(ASM(
            'POP',
            table_stack[-1].get(Symbol.TEMP_A_KEY).get('memory')
        ))
        table_stack[-1].get(Symbol.TEMP_A_KEY).set('type', table_stack[-1].get(Symbol.TEMP_C_KEY).get('type'))

        left_arg = table_stack[-1].get(Symbol.TEMP_A_KEY).get('memory')

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

    output.append(ASM(
        ASM.wrap_type('PUSH', node.get('type')),
        table_stack[-1].get(Symbol.TEMP_C_KEY).get('memory')
    ))

    return output

def generate_if(table_stack, node):
    output = []

    condition = node.args[0]
    body = node.args[1]

    true_label = new_label()
    false_label = new_label()

    # deal with the jump
    condition_left = condition.args[0]
    condition_right = condition.args[1]

    if condition_left.get('name') in KNOWN:
        if condition_left.get('name') == 'identifier':
            condition_left_symbol = table_stack[-1].get(condition_left.symbol) or table_stack[0].get(condition_left.symbol)
            condition_left_arg = condition_left_symbol.get('memory')
        else:
            condition_left_arg = ASM.constant(condition_left.symbol)
    else:
        output.append(generate_expr(table_stack, condition_left))
        output.append(ASM(
            'POP',
            table_stack[-1].get(Symbol.TEMP_A_KEY).get('memory')
        ))
        table_stack[-1].get(Symbol.TEMP_A_KEY).set('type', table_stack[-1].get(Symbol.TEMP_C_KEY).get('type'))
        condition_left_arg = table_stack[-1].get(Symbol.TEMP_A_KEY).get('memory')

    if condition_right.get('name') in KNOWN:
        if condition_right.get('name') == 'identifier':
            condition_right_symbol = table_stack[-1].get(condition_right.symbol) or table_stack[0].get(condition_right.symbol)
            condition_right_arg = condition_right_symbol.get('memory')
        else:
            condition_right_arg = ASM.constant(condition_right.symbol)
    else:
        output.append(generate_expr(table_stack, condition_right))
        output.append(ASM(
            'POP',
            table_stack[-1].get(Symbol.TEMP_B_KEY).get('memory')
        ))
        table_stack[-1].get(Symbol.TEMP_B_KEY).set('type', table_stack[-1].get(Symbol.TEMP_C_KEY).get('type'))
        condition_right_arg = table_stack[-1].get(Symbol.TEMP_B_KEY).get('memory')

    output.append(ASM(
        ASM.wrap_type(ASM.BOOLEAN_OPERATION_MAP[condition.symbol], condition.get('type')),
        condition_left_arg,
        condition_right_arg,
        true_label
    ))

    # this is to catch if the condition is not met
    output.append(ASM('JUMP', false_label))
    output.append(ASM('LABEL', true_label))

    output.append(generate_body(table_stack, body))

    if len(node.args) == 3:
        post_label = new_label()

        output.append(ASM('JUMP', post_label))

        output.append(ASM('LABEL', false_label))
        else_body = node.args[2]

        output.append(generate_body(table_stack, else_body))

        output.append(ASM('LABEL', post_label))
    else:
        output.append(ASM('LABEL', false_label))

    return output

def generate_while(table_stack, node):
    output = []

    condition = node.args[0]
    body = node.args[1]

    pre_label = new_label()
    true_label = new_label()
    false_label = new_label()

    output.append(ASM('LABEL', pre_label))

    condition_left = condition.args[0]
    condition_right = condition.args[1]

    if condition_left.get('name') in KNOWN:
        if condition_left.get('name') == 'identifier':
            condition_left_symbol = table_stack[-1].get(condition_left.symbol) or table_stack[0].get(condition_left.symbol)
            condition_left_arg = condition_left_symbol.get('memory')
        else:
            condition_left_arg = ASM.constant(condition_left.symbol)
    else:
        output.append(generate_expr(table_stack, condition_left))
        output.append(ASM(
            'POP',
            table_stack[-1].get(Symbol.TEMP_A_KEY).get('memory')
        ))
        table_stack[-1].get(Symbol.TEMP_A_KEY).set('type', table_stack[-1].get(Symbol.TEMP_C_KEY).get('type'))
        condition_left_arg = table_stack[-1].get(Symbol.TEMP_A_KEY).get('memory')

    if condition_right.get('name') in KNOWN:
        if condition_right.get('name') == 'identifier':
            condition_right_symbol = table_stack[-1].get(condition_right.symbol) or table_stack[0].get(condition_right.symbol)
            condition_right_arg = condition_right_symbol.get('memory')
        else:
            condition_right_arg = ASM.constant(condition_right.symbol)
    else:
        output.append(generate_expr(table_stack, condition_right))
        output.append(ASM(
            'POP',
            table_stack[-1].get(Symbol.TEMP_B_KEY).get('memory')
        ))
        table_stack[-1].get(Symbol.TEMP_B_KEY).set('type', table_stack[-1].get(Symbol.TEMP_C_KEY).get('type'))
        condition_right_arg = table_stack[-1].get(Symbol.TEMP_B_KEY).get('memory')

    output.append(ASM(
        ASM.wrap_type(ASM.BOOLEAN_OPERATION_MAP[condition.symbol], condition.get('type')),
        condition_left_arg,
        condition_right_arg,
        true_label
    ))

    # this is to catch if the condition is not met
    output.append(ASM('JUMP', false_label))
    output.append(ASM('LABEL', true_label))

    output.append(generate_body(table_stack, body))

    output.append(ASM('JUMP', pre_label))

    output.append(ASM('LABEL', false_label))

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
        table.set(Symbol.TEMP_A_KEY, Symbol(SymbolScope.LOCAL, SymbolType.OTHER, attrs={'memory': new_memory()}))
        table.set(Symbol.TEMP_B_KEY, Symbol(SymbolScope.LOCAL, SymbolType.OTHER, attrs={'memory': new_memory()}))
        table.set(Symbol.TEMP_C_KEY, Symbol(SymbolScope.LOCAL, SymbolType.OTHER, attrs={'memory': new_memory()}))
