class SymbolTableError(Exception):
    pass


class ParseError(Exception):
    pass


ERROR = False


def set_error():
    global ERROR
    ERROR = True
