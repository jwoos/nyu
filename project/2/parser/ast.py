class Node:
    def __init__(self, symbol, args=None, attrs=None, terminal=False):
        # what is the symbol
        self.symbol = symbol

        # what are the arguments to this
        self.args = args
        if self.args is None:
            self.args = []

        # terminal
        self.terminal = terminal

        self.attrs = attrs
        if self.attrs is None:
            self.attrs = {}
