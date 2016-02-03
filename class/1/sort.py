# Junwoo Shin
# Jacky Teoh
# Abir Hassan
# Jonathan Poch
# Sindhu Avuthu

def get_list():
    the_list = []
    item = ''
    while item != 'done':
        item = input('Please enter a number: ')
        if item != 'done':
            the_list.append(int(item))
    return the_list

def sort(the_list):
    sorted = []

    for x in range(len(the_list) - 1, -1, -1):
        max = 0
        for y in range(0, x + 1):
            if the_list[y] > max:
                max = the_list[y]
        the_list.pop(the_list.index(max))
        if (not sorted):
            sorted = [max]
        else:
            sorted = [max] + sorted

    return sorted

def main():
    the_list = get_list()
    sorted = sort(the_list)
    print(sorted)
    return(sorted)

main()
