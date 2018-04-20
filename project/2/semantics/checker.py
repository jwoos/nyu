import enum

from log import logger
from semantics.symbol_table import SymbolTable, SymbolScope, SymbolType, Symbol, info


@enum.unique
class InferredType(enum.Enum):
    ANY = 1
    CONFLICT = 2


INFERRED_TYPE_SET = set(InferredType)
PROPAGATING_BINARY_SYMBOLS = {'=', '*', '/', '+', '-', '<=', '>=', '==', '<', '>'}
PROPAGATING_UNARY_SYMBOLS = {'return', '-'}
TERMINALS = {'float_literal', 'integer_literal', 'identifier'}
NAME_MAP = {
    '=': 'assigning',
    '*': 'multiplying',
    '/': 'dividng',
    '+': 'adding',
    '-': 'subtracting',
    '<=': 'comparing',
    '>=': 'comparing',
    '==': 'comparing',
    '<': 'comparing',
    '>': 'comparing'
}


def propagate_types(node_stack, table_stack, node):
    if not node:
        logger.warning('encountered empty node during type propagation')
        return None

    elif node.attrs.get('name') in TERMINALS or node.attrs['type']:
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
    types = [propagate_types(node_stack, table_stack, c) for c in children]

    if not types:
        return None

    t = None
    modified = False
    for x in types:
        if not x:
            continue

        if x != t:
            if t not in INFERRED_TYPE_SET and x not in INFERRED_TYPE_SET:
                node.attrs['type'] = InferredType.CONFLICT
                modified = True
            else:
                node.attrs['type'] = InferredType.ANY
                modified = True

        t = x

    if not modified:
        node.attrs['type'] = types[0]

    return node.attrs['type']

def check_unary(node_stack, table_stack, node):
    single = node.args[0]

    inferred_type = propagate_types(node_stack, table_stack, single)

    node.attrs['type'] = inferred_type

# this deals with mulop, addop, assignment, boolop
def check_binary(node_stack, table_stack, node):
    left = node.args[0]
    left_symbol = table_stack[-1].get(left.symbol) or table_stack[0].get(left.symbol) or Symbol(None, None, attrs={'line': None})
    left_type = propagate_types(node_stack, table_stack, left)

    right = node.args[1]
    right_symbol = table_stack[-1].get(right.symbol) or table_stack[0].get(right.symbol) or Symbol(None, None, attrs={'line': None})
    right_type = propagate_types(node_stack, table_stack, right)

    if left_type != right_type:
        if left_type not in INFERRED_TYPE_SET and right_type not in INFERRED_TYPE_SET:
            logger.error(
                f'Type error on line {node.attrs.get("line")}'
                f': {NAME_MAP[node.symbol]} ({node.symbol}) {left_type} {left} [{left.attrs.get("name")}] (declared on line {left_symbol.attrs.get("line") or node.attrs.get("line")}) '
                f'with {right_type} {right} [{right.attrs.get("name")}] (declared on line {right.attrs.get("line") or node.attrs.get("line")})'
            )
            node.attrs['type'] = InferredType.CONFLICT
        else:
            node.attrs['type'] =  InferredType.ANY
    else:
        node.attrs['type'] = left_type

    return node.attrs['type']

def check_function_call(node_stack, table_stack, node):
    identifier = node.args[0]
    identifier_symbol = table_stack[0].get(identifier.symbol) or Symbol(None, None, attrs={'line': None})
    identifier_type = identifier_symbol.attrs['arg_type']

    body = node.args[1]
    body_symbol = table_stack[-1].get(body.symbol) or table_stack[0].get(body.symbol) or Symbol(None, None, attrs={'line': None})
    body_type = propagate_types(node_stack, table_stack, body)

    if identifier_type != body_type:
        if identifier_type not in INFERRED_TYPE_SET and body_type not in INFERRED_TYPE_SET:
            logger.error(
                f'Type error calling function {identifier.symbol} '
                f'(declared on line {identifier_symbol.attrs.get("line")}) '
                f'with {body_type} but expected type {identifier_type}'
            )
            node.attrs['type'] = InferredType.CONFLICT
        else:
            node.attrs['type'] = InferredType.ANY
    else:
        node.attrs['type'] = identifier_type

    return node.attrs['type']
