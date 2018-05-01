class Memory:
    def __init__(self):
        self.size = 0
        self.memory = {}
        self.labels = {}


class MemoryItem:
    def __init__(self, item, size):
        self.size = size
        self.item = item
