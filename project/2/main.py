import sys
import os

from parser.ast import Node
from parser.parser import parser
from scanner.scanner import lexer
from semantics.symbol_table import SymbolTable, SymbolScope, SymbolType, Symbol, info
from semantics import handler, type_check
from log import logger


def main():
    s = None
    if len(sys.argv) > 1:
        s = open(sys.argv[1]).read()
    else:
        s = open('test.c').read()
    result = parser.parse(s)
    logger.info(result)

    if result is None:
        logger.error('AST is None - exiting')
        return

    node_stack = [result]
    table_cache = {}
    table_stack = [SymbolTable(SymbolScope.GLOBAL)]

    while node_stack:
        node = node_stack.pop()
        logger.debug(node)

        if node.symbol == 'function_def':
            signal = handler.handle_function_def(node_stack, table_stack, table_cache, node)
            if signal == handler.Signal.CONTINUE:
                continue

        elif node.symbol == 'function_def_end':
            handler.handle_function_def_end(node_stack, table_stack, table_cache, node)

        elif node.symbol == 'function_decl':
            handler.handle_function_decl(node_stack, table_stack, table_cache, node)

        elif node.symbol == 'decl':
            handler.handle_decl(node_stack, table_stack, table_cache, node)

        elif node.attrs.get('name') == 'identifier':
            handler.handle_identifier(node_stack, table_stack, table_cache, node)

        else:
            # if node.attrs.symbol in ('=', 'function_call', '+', '-', '/', '*'):

            for child in reversed(node.args):
                if child:
                    node_stack.append(child)

    if 'main' not in table_stack[0].table:
        logger.error('main is not defined')


if __name__ == '__main__':
    main()
