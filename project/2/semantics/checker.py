import enum

from log import logger
from semantics.symbol_table import SymbolTable, SymbolScope, SymbolType, Symbol, info


@enum.unique
class InferredType(enum.Enum):
    ANY = 1
    CONFLICT = 2


INFERRED_TYPE_SET = set(InferredType)


def propapagate_type(node_stack, table_stack, node):
    if not node:
        logger.warning('encountered empty node during type propagation')
        return None

    elif node.attrs.get('name') == 'identifier':
        # check if the node has a type
        t = node.attrs.get('type')
        if not t:
            # check the symbol table for a type
            symbol = table_stack[-1].get(node.symbol)

            # doesn't exist
            if not symbol:
                node.attrs['type'] = InferredType.ANY

            else:
                if not symbol.attrs.get('type'):
                    symbol.attrs['type'] = InferredType.ANY
                    node.attrs['type'] = InferredType.ANY
                else:
                    node.attrs['type'] = symbol.attrs['type']

        return node.attrs['type']

    children = node.args
    types = [propapagate_type(node_stack, table_stack, c) for c in children]

    t = None
    for x in types:
        if not x:
            continue

        t = x

        if x != t:
            if t not in INFERRED_TYPE_SET and x not in INFERRED_TYPE_SET:
                return InferredType.CONFLICT
            else:
                return InferredType.ANY

    return types[0]

# uminus
def check_unary(node_stack, table_stack, node):
    single = node.args[0]

    node.attrs['type'] = propapagate_type(node_stack, table_stack, node)

# this deals with mulop, addop, assignment
def check_binary(node_stack, table_stack, node):
    left = node.args[0]
    left_type = propapagate_type(node_stack, table_stack, left)

    right = node.args[1]
    right_type = propapagate_type(node_stack, table_stack, right)

    if left_type != right_type:
        if left_type not in INFERRED_TYPE_SET and right_type not in INFERRED_TYPE_SET:
            return InferredType.CONFLICT
        else:
            return InferredType.ANY

    node.attrs['type'] = left_type

def check_function_call(node_stack, table_stack, node):
    pass
