from code.asm import ASM
from code.memory import Stack, Memory, Label, Function, new_memory
from semantics.symbol_table import SymbolType, Symbol, SymbolScope, RETURN_KEY


def generate(ast, table_cache, global_table):
    output = []
    stack = Stack()
    node_stack = [ast]
    table_stack = [global_table]

    table = None

    # initialize globals
    generate_memory(table_stack[0], False)

    return

    while node_stack:
        node = node_stack.pop()

        if node.symbol == 'function_def':
            # 0 is identifier for function
            # 1 is function argument
            # 2 is function body
            generate_function(stack, node_stack, table_stack, node)

        for child in reversed(node.args):
            if child:
                node_stack.append(child)

    return output

# everything can be dealt with in here since only functions
# can have any operations or calls
def generate_function(stack, node_stack, table_stack, function):
    function_identifier = function.args[0]
    function_argument = function.args[1]
    function_body = function.args[2]

    table_stack.append(table_cache[function_identifier.symbol])

    node_stack.append(function_body)

    output = []
    # generate local variables
    generate_memory(table_stack[-1], True)
    function_symbol = table_stack[0].get(function.args[0].symbol)

    output.append(ASM('LABEL', function_symbol.attrs['label']))
    # pop the argument into the parameter
    output.append(ASM('POP', table_stack[-1].get(function_argument.symbol)))

    while node_stack:
        node = node_stack.pop()

        if node.symbol == 'return':
            output.append(ASM('PUSH', table_stack[-1].get(RETURN_KEY)))
            table_stack.pop()
            return
        elif node.symbol == 'write':
            pass
        elif node.symbol == 'read':
            pass
        elif node.symbol == 'function_call':
            pass

        # calling main for the first time
        if not stack.size():
            pass
        else:
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
        table[RETURN_KEY] = Symbol(SymbolScope.LOCAL, SymbolType.OTHER, attrs={'memory': new_memory()})
