from enum import Enum

from log import logger
from semantics.symbol_table import SymbolTable, SymbolScope, SymbolType, Symbol, info




class InferredType(Enum):
    ANY = 1
    CONFLICT = 2
    INT = 3
    FLOAT = 4


def propapagate_type(node_stack, table_stack, node):
    if not node:
        logger.warning('encountered empty node during propagation')
        return None
    elif node.attrs.get('name') == 'identifier':
        t = node.attrs.get('type')
        if not t:
            table_stack[-1].get(node.symbol)
        node.attrs['inferred_type'] = node.attrs.get('type')
        return node.attrs.get('type')

    children = node.args
    types = [propapagate_type(node_stack, table_stack, c) for c in children]

    t = None
    for x in types:
        if not x:
            continue

        t = x

        if x != t:
            if t not in (InferredType.ANY, InferredType.CONFLICT) and x not in (InferredType.ANY, InferredType.CONFLICT):
                return InferredType.CONFLICT
            else:
                return InferredType.ANY

    return types[0]



def check_addop(node_stack, table_stack, node):
    pass

def check_mulop(node_stack, table_stack, node):
    pass

def check_assignment(node_stack, table_stack, node):
    left = node.args[0]
    left_symbol = table_stack[-1].get(left.symbol)
    if left_symbol is None:
        left_symbol = Symbol(
            SymbolScope.ANY,
            SymbolScope.VARIABLE,
            {
                'type': InferredType.ANY
            }
        )

    right = node.args[1]
    stack = []

def check_function_call(node_stack, table_stack, node):
    pass
