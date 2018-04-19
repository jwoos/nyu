import sys
import os

from parser.ast import Node
from parser.parser import parser
from scanner.scanner import lexer
from semantics.symbol_table import SymbolTable, SymbolScope, SymbolType, Symbol, info
from semantics import handler, checker
from log import logger


PROPAGATING_SYMBOLS = {'+', '-', '<=', '>=', '==', '<', '>', '*', '/', 'function_call', '='}


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
    table_stack = [SymbolTable(SymbolScope.GLOBAL)]

    while node_stack:
        node = node_stack.pop()
        logger.debug(node)

        if node.symbol == 'function_def':
            signal = handler.handle_function_def(node_stack, table_stack, node)
            if signal == handler.Signal.CONTINUE:
                continue

        elif node.symbol == 'function_def_end':
            handler.handle_function_def_end(node_stack, table_stack, node)

        elif node.symbol == 'function_decl':
            handler.handle_function_decl(node_stack, table_stack, node)

        elif node.symbol == 'decl':
            handler.handle_decl(node_stack, table_stack, node)

        else:
            if node.attrs.get('name') == 'identifier':
                if table_stack[-1].get(node.symbol) is None:
                    if table_stack[-1].scope == SymbolScope.LOCAL and table_stack[0].get(node.symbol) is None:
                        logger.error(f'{node.symbol} referenced before declaration')
                    else:
                        info(table_stack[0].get(node.symbol), usage=node.attrs.get('line', True))
                else:
                    info(table_stack[-1].get(node.symbol), usage=node.attrs.get('line', True))
                continue

            elif node.symbol == 'function_call':
                func = table_stack[0].get(node.args[0].symbol)
                if func:
                    func.attrs['call'] = True
                    checker.check_function_call(node_stack, table_stack, node)

            elif node.symbol == '=':
                checker.check_assignment(node_stack, table_stack, node)

            for child in reversed(node.args):
                if child:
                    node_stack.append(child)

    # check if a declared function was called, it was later defined
    for v in table_stack[0].table.values():
        if not v.attrs.get('init') and v.attrs.get('call'):
            logger.error(f'Function {v} declared and called but never defined')

    # check if main was defined
    if 'main' not in table_stack[0].table:
        logger.error('main is not defined')


if __name__ == '__main__':
    main()
