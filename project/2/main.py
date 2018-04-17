from collections import deque

from parser.ast import Node
from parser.parser import parser
from scanner.scanner import lexer
from parser.table import SymbolTable, SymbolScope, SymbolType, Symbol, info
from log import logger


def main():
    s = open('test.c').read()
    result = parser.parse(s)
    print(result)

    node_stack = [result]
    table_stack = [SymbolTable(SymbolScope.GLOBAL)]

    while node_stack:
        node = node_stack.pop()
        logger.debug(node)

        if node.symbol == 'function_def':
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
                logger.error(msg)
                continue

            table_stack.append(SymbolTable(SymbolScope.LOCAL))
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
            node_stack.append(Node('function_def_end'))
            node_stack.append(node.args[1])
        elif node.symbol == 'function_def_end':
            table_stack.pop()
        elif node.symbol == 'function_decl':
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
                logger.error(msg)
        elif node.symbol == 'decl':
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
                    logger.error(msg)
        else:
            if node.attrs.get('type') == 'identifier':
                if table_stack[-1].get(node.symbol) is None:
                    if table_stack[0].get(node.symbol) is None:
                        logger.error(f'{node.symbol} referenced before declaration')
                    else:
                        info(table_stack[0].get(node.symbol), usage=node.attrs.get('line', True))
                else:
                    info(table_stack[-1].get(node.symbol), usage=node.attrs.get('line', True))
            else:
                for child in reversed(node.args):
                    if child:
                        node_stack.append(child)

    if 'main' not in table_stack[0].table:
        logger.error('main is not defined')


if __name__ == '__main__':
    main()
