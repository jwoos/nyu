import enum


@enum.unique
class OperatorType(enum.Enum):
    UNARY = 1
    BINARY = 2
    TRINARY = 3
    N_ARY = 4
    OTHER = 5


class Node:
    PSEUDO_SYMBOL = '<PSEUDO>'

    def __init__(self, symbol, args=None, attrs=None):
        # what is the symbol
        self.symbol = symbol

        # what are the arguments to this
        self.args = args
        if self.args is None:
            self.args = []

        self.attrs = {
            'name': None,
            'type': None,
            'line': None,
            'terminal': False,
            'operator': None,
        }
        if attrs is not None:
            self.attrs.update(attrs)

    def __str__(self):
        if not self.args:
            # return f'{self.symbol} {{{self.attrs.get("type")}}}'
            return f'{self.symbol}'
        else:
            return f'{self.symbol} : ({self.args})'

    def __repr__(self):
        return self.__str__()

    def get(self, key):
        return self.attrs.get(key)

    def set(self, key, val):
        self.attrs[key] = val
