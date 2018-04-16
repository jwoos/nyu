class Node:
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
        }
        if attrs is not None:
            self.attrs.update(attrs)

    def __str__(self):
        if not self.args:
            return f'{self.symbol}'
        else:
            return f'{self.symbol} : ({self.args})'

    def __repr__(self):
        return self.__str__()
