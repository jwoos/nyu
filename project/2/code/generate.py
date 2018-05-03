class Label:
    def __init__(self, index, items=None, attrs={}):
        self.index = index
        self.items = []
        if items is not None:
            self.items items


label_index = 0


def label():
    global label_index
    val = Label(label_index)
    label_index += 1
    return val
