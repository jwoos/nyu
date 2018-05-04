class ASM:
    NUMERICAL_OPERATION_MAP = {
        '+': 'ADD',
        '-': 'SUB',
        '*': 'MUL',
        '/': 'DIV'
    }

    def __init__(self, operation, *args):
        self.operation = operation
        self.operands = args
        if args:
            self.operands = args

    def __str__(self):
        if self.operands:
            return f'{self.operation} {" ".join([str(x) for x in self.operands])}'
        else:
            return f'{self.operation}'

    def __repr__(self):
        return self.__str__()

    @staticmethod
    def normal(val):
        return f'{val}'

    @staticmethod
    def literal(val):
        return f'#{val}'

    @staticmethod
    def indirect(val):
        return f'@{val}'

    @staticmethod
    def string(val):
        return f'"{val}"'

    @staticmethod
    def constant(val):
        return f'#{val}'

    @staticmethod
    def wrap_type(val, _type):
        if _type == int:
            return val
        elif _type == float:
            return f'{val}F'
        else:
            return f'{val}S'
