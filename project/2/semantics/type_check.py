from semantics.symbol_table import SymbolTable, SymbolScope, SymbolType, Symbol, info


class Any:
    pass


def check_addop(node_stack, table_stack, table_cache, node):
    pass

def check_mulop(node_stack, table_stack, table_cache, node):
    pass

def check_assignment(node_stack, table_stack, table_cache, node):
    left = node.args[0]
    left_symbol = table_stack[-1].get(left.symbol)
    if left_symbol is None:
        left_symbol = Symbol(
            SymbolScope.ANY,
            SymbolScope.VARIABLE,
            {
                'type': Any
            }
        )

    right = node.args[1]
    stack = []
