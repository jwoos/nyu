def all_value(iterable, value):
    return all([x == value for x in iterable])

def flatten_array(arr):
    output = []
    for item in arr:
        if isinstance(item, list):
            for sub in flatten_array(item):
                output.append(sub)
        else:
            output.append(item)

    return output
