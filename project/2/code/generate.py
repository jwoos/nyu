from code.asm import ASM
from code.memory import Stack, Memory, Label, Function, new_memory, new_label
from parser.ast import Node
from semantics.symbol_table import SymbolType, Symbol, SymbolScope


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
                elif arg.get('name') == 'int_literal':
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
                    print(arg)
                    # TODO deal with expressions
                    # this is an expression
                    pass

                # there should be a space between all the items being written
                output.append(ASM('WRITES', ASM.string(' ')))

            # newline after writing is done
            output.append(ASM('NEWLINE'))

        elif node.symbol == 'read':
            for arg in node.args:
                if arg.get('name') == 'identifier':
                    identifier_symbol = table_stack[-1].get(arg.symbol) or table_stack[0].get(arg.symbol)

                    if identifier_symbol.get('type') == int:
                        output.append(ASM('READ', identifier_symbol.get('memory')))
                    else:
                        output.append(ASM('READF', identifier_symbol.get('memory')))
                else:
                    print(arg)
                    # TODO deal with expressions
                    # this is an expression
                    pass

        elif node.symbol == 'function_call':
            pass

        for child in reversed(node.args):
            if child:
                node_stack.append(child)

def generate_function_call(stack, node_stack, table_stack, node):
    pass

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
        table.set(Symbol.TEMP_KEY, Symbol(SymbolScope.LOCAL, SymbolType.OTHER, attrs={'memory': new_memory()}))
