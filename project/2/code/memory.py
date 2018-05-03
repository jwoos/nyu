memory_index = 0


def new_memory():
    global memory_index
    index = memory_index
    memory_index += 1
    return index


class Memory:
    def __init__(self, item, attrs={}):
        global memory_index
        self.index = memory_index
        memory_index += 1

        self.item = item

        self.attrs = {}
        if attrs is not None:
            self.attrs = attrs


label_index = 0


def new_label():
    global label_index
    index = label_index
    label_index += 1
    return index


class Label:
    def __init__(self, items=None, attrs=None):
        global label_index
        self.index = label_index
        label_index += 1

        self.items = []
        if items is not None:
            self.items = items

        self.attrs = {}
        if attrs is not None:
            self.attrs = attrs

    def __str__(self):
        return f'<Label: {self.index}>'

    def __repr__(self):
        return self.__str__()


class Function:
    def __init__(self):
        global label_index
        self.index = label_index
        label_index += 1

        self.items = []

    def __str__(self):
        return f'<Label: {self.index}>'

    def __repr__(self):
        return self.__str__()


class Stack:
    def __init__(self):
        self.memory = []

    def push(self, item):
        self.memory.append(item)

    def pop(self):
        return self.memory.pop()

    def size(self):
        return len(self.memory)


class Frame:
    def __init__(self, items):
        self.items = items
