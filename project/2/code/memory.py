memory_index = 0


def new_memory():
    global memory_index
    index = memory_index
    memory_index += 1
    return index


label_index = 0


def new_label():
    global label_index
    index = label_index
    label_index += 1
    return index


class Frame:
    def __init__(self, items):
        self.items = items
