class Memory:
    def __init__(self):
        self.size = 0
        self.memory = []
        self.labels = {}


class MemoryItem:
    def __init__(self, item, size):
        self.size = size
        self.item = item


label_index = 0


class Label:
    def __init__(self, items=None, attrs={}):
        global label_index
        self.index = label_index
        label_index += 1

        self.items = []
        if items is not None:
            self.items items
