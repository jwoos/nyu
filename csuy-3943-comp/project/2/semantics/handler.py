import enum

from parser.ast import Node
from semantics.symbol_table import SymbolTable, SymbolScope, SymbolType, Symbol, info
from semantics import checker
import log


@enum.unique
class Signal(enum.Enum):
    CONTINUE = 1
    STOP = 2
    NULL = 3


def handle_function_def(node_stack, table_stack, node):
    msg = table_stack[0].set(node.args[0].symbol, Symbol(
        table_stack[0].scope,
        SymbolType.FUNCTION,
        {
            'init': True,
            'type': node.args[0].attrs['type'],
            'name': node.args[0],
            'arg_type': node.args[1].attrs['type'],
            'arg': node.args[1],
            'line': node.attrs['line']
        }
    ))
    info(table_stack[0].get(node.args[0].symbol), usage=False)
    if msg:
        log.error(msg)
        return Signal.CONTINUE

    table_stack.append(SymbolTable(SymbolScope.LOCAL, name=node.args[0].symbol))
    table_stack[-1].set(node.args[1].symbol, Symbol(
        table_stack[-1].scope,
        SymbolType.VARIABLE,
        {
            'value': None,
            'type': node.args[1].attrs['type'],
            'name': node.args[1],
            'line': node.attrs.get('line')
        }
    ))

    # psuedo node to mark function exit
    node_stack.append(Node(
        'function_def_end',
        args=[node.args[0]],
        attrs={}
    ))

    return_node = None

    node_stack.append(node.args[2])

def handle_function_def_end(node_stack, table_stack, node):
    function_table = table_stack.pop()

def handle_function_decl(node_stack, table_stack, node):
    msg = table_stack[0].set(node.args[0].symbol, Symbol(
        SymbolScope.GLOBAL,
        SymbolType.FUNCTION,
        {
            'init': False,
            'type': node.args[0].attrs['type'],
            'name': node.args[0],
            'arg_type': node.attrs['type'],
            'arg': None,
            'line': node.attrs['line']
        }
    ))
    info(table_stack[0].get(node.args[0].symbol), usage=False)
    if msg:
        log.error(msg)

def handle_decl(node_stack, table_stack, node):
    for var in node.args:
        msg = table_stack[-1].set(var.symbol, Symbol(
            table_stack[-1].scope,
            SymbolType.VARIABLE,
            {
                'value': None,
                'type': node.attrs['type'],
                'name': var,
                'line': var.attrs['line']
            }
        ))
        info(table_stack[-1].get(var.symbol), usage=False)
        if msg:
            log.error(msg)
