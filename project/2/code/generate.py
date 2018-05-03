from code.memory import Memory, Label


def generate(ast, table_cache):
    memory = Memory()
    node_stack = [ast]

    while node_stack:
        node = node_stack.pop()

        if node.symbol == 'function_def':
            new_label = Label()
            new_label.attrs

        for child in reversed(node.args):
            if child:
                node_stack.append(child)
