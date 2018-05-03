class ASM:
    def __init__(self, operation, operands=None):
        self.operation = operation
        self.operands = []
        if operands:
            self.operands = operands

    def __str__(self):
        return f'{self.operation} {" ".join(self.operands)}'

    def __repr__(self):
        return self.__str__()
