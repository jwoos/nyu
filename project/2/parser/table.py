from enum import Enum
import json

from parser.ast import Node


class CustomEncoder(json.JSONEncoder):
    def default(self, o):
        if isinstance(o, Symbol) or isinstance(o, Node):
            return o.__str__()
        else:
            return super().default(o)


class SymbolScope(Enum):
    LOCAL = 1
    GLOBAL = 2
    ANY = 3


class SymbolType(Enum):
    FUNCTION = 1
    VARIABLE = 2


class Symbol:
    def __init__(self, scope, kind, attrs=None):
        self.scope = scope
        self.kind = kind

        self.attrs = attrs
        if not attrs:
            self.attrs = {}

    def __str__(self):
        return f'<Symbol {self.scope} {self.kind} {json.dumps(self.attrs, cls=CustomEncoder)}>'

    def __repr__(self):
        return self.__str__()


class SymbolTable:
    def __init__(self, scope):
        self.scope = scope
        self.table = {}

    def __str__(self):
        return json.dumps(self.table, indent=True, cls=CustomEncoder)

    def __repr__(self):
        return self.__str__()

    def get(self, key):
        return self.table.get(key, None)

    def set(self, key, symbol):
        if symbol.kind == SymbolType.FUNCTION:
            table_symbol = self.table.get(key)
            if table_symbol and table_symbol.attrs['init']:
                return f'function {key} already defined'

            if table_symbol:
                # make sure all properties are good
                for prop in ('type', 'arg_type'):
                    if symbol.attrs[prop].symbol != table_symbol.attrs[prop].symbol:
                        return f'Type mistmatch - declared is {table_symbol.attrs[prop]} and defined is {symbol.attrs[prop]}'

                table_symbol.attrs = symbol.attrs
        else:
            if self.table.get(key):
                return 'Already defined'

        self.table[key] = symbol

    def clear(self):
        self.table = {}

