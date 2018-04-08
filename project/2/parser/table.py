from enum import Enum


class Scope(Enum):
    LOCAL = 1
    GLOBAL = 2
    ANY = 3


class SymbolTable:
    def __init__(self, scope):
        self.scope = scope
        self.table = {}

    def get(self, key):
        val = self.table.get(key, None)
        if val is None:
            raise SymbolTableError()

    def set(self, key, value):
        if self.get(key):
            raise SymbolTableError()

        self.table[key] = value

    def clear(self):
        self.table = {}
