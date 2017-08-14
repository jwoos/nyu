def max_abs_val(lst):
    maximum = lst[0]
    for i in lst:
        if i < 0:
            i = -i
        if i > maximum:
            maximum = i
    return maximum


def main_q1():
    lst = [-19, -3, 20, -1, 0, -25]
    max_num = max_abs_val(lst)
    print('In %s the max absolute number is %s' % (lst, max_num))
main_q1()


def find_all(lst, val):
    solution = []
    for elem in range(len(lst)):
        if lst[elem] == val:
            solution.append(elem)
    return solution


def main_q2():
    lst = ['a', 'b', 10, 'bb', 'a']
    val = 'a'
    indices = find_all(lst, val)
    print('In %s the value %s appears in the following indices: %s' % (lst, val, indices))
main_q2()


def reverse1(lst):
    reversed_list = lst[::-1]
    return reversed_list


def reverse2(lst):
    for i in range(len(lst) - 1, -1, -1):
        lst.append(lst.pop(i))
    return lst


def main_q3():
    lst1 = [1, 2, 3, 4, 5, 6]
    rev_lst1 = reverse1(lst1)
    print('After reverse1, lst1 is ', lst1, 'and the returned list is', rev_lst1)
    lst2 = [1, 2, 3, 4, 5, 6]
    reverse2(lst2)
    print('After reverse2, lst2 is ', lst2)
main_q3()


def encoder(a_string):
    encoded = []
    index = 0

    while index < len(a_string):
        count = 0
        current_val = a_string[index]
        while index < len(a_string) and current_val == a_string[index]:
            count += 1
            index += 1

        encoded.append([current_val, count])
    return encoded


def decoder(a_list):
    decoded = ''
    for elem in a_list:
        decoded += elem[0] * elem[1]
    return decoded


def main_q4():
    encode_this = 'aadccccaa'
    encoded = encoder(encode_this)
    print('Text to encode was %s, encoded text is %s' % (encode_this, encoded))
    decode_this = [['a', 2], ['d', 1], ['c', 4], ['a', 2]]
    decoded = decoder(decode_this)
    print('Text to decode was %s, decoded text is %s' % (decode_this, decoded))
main_q4()


def add_list(lst1, lst2):
    solution = []
    for index in range(len(lst1)):
        solution.append(lst1[index] + lst2[index])
    return solution


def main_q5():
    lst1 = []
    input1 = 0
    print('Enter the first list of numbers')
    while input1 != 'done':
        input1 = input('Enter a number: ')
        if input1 != 'done':
            lst1.append(int(input1))

    print('Enter the second list of numbers')
    lst2 = []
    input2 = 0
    while input2 != 'done':
        input2 = input('Enter a number: ')
        if input2 != 'done':
            lst2.append(int(input2))

    if len(lst1) == len(lst2):
        the_sum_list = add_list(lst1, lst2)
        for x in the_sum_list:
            print(x)
    else:
        print('The lists are different lengths!')
main_q5()


def create_prefix_list(lst):
    big_list = []
    for index in range(len(lst) + 1):
        big_list.append(lst[0:index:])
    return big_list


def main_q6():
    the_list = [2, 4, 6, 8, 10]
    prefixed = create_prefix_list(the_list)
    print('The list was %s and the list of prefixes is %s' % (the_list, prefixed))
main_q6()


def check_sudoku(lst):
    row = None
    for a_row in lst:
        duplicate = False
        for index in range(9):
            temp = lst[:]
            if temp.pop(index) in temp:
                duplicate = True
        if duplicate is True:
            row = False
        else:
            row = True

    column = None
    for index in range(9):
        duplicate = False
        column_list = []
        for a_row in lst:
            column_list.append(a_row[index])
        for index in range(9):
            temp = column_list[:]
            if temp.pop(index) in temp:
                duplicate = True
        if duplicate is True:
            column = False
        else:
            column = True

    ordered = []
    for offsety in range(0, 7, 3):
        for offsetx in range(0, 7, 3):
            for y in range(offsety, 3 + offsety):
                for x in range(offsetx, 3 + offsetx):
                    ordered.append(lst[x][y])

    for section in range(9):
        duplicate = None
        for index in range(9):
            temp = ordered[9 * section: 9 * (section + 1)]
            if temp.pop(index) in temp:
                duplicate = True
        if duplicate is True:
            grid = False
        else:
            grid = True

    if column is False or row is False or grid is False:
        return False
    elif column is True and row is True and grid is True:
        return True


def main_q7():
    board1 = [
        [5, 3, 4, 6, 7, 8, 9, 1, 2],
        [6, 7, 2, 1, 9, 5, 3, 4, 8],
        [1, 9, 8, 3, 4, 2, 5, 6, 7],
        [8, 5, 9, 7, 6, 1, 4, 2, 3],
        [4, 2, 6, 8, 5, 3, 7, 9, 1],
        [7, 1, 3, 9, 2, 4, 8, 5, 6],
        [9, 6, 1, 5, 3, 7, 2, 8, 4],
        [2, 8, 7, 4, 1, 9, 6, 3, 5],
        [3, 4, 5, 2, 8, 6, 1, 7, 9]
    ]

    board2 = [
        [5, 3, 4, 6, 7, 8, 9, 1, 2],
        [6, 7, 2, 1, 9, 5, 3, 4, 8],
        [1, 9, 8, 3, 4, 2, 5, 9, 7],
        [8, 5, 9, 7, 6, 1, 4, 2, 3],
        [4, 3, 6, 8, 5, 3, 7, 9, 1],
        [7, 1, 3, 9, 2, 4, 8, 5, 6],
        [9, 6, 1, 5, 3, 7, 2, 8, 4],
        [2, 8, 9, 4, 1, 9, 6, 3, 5],
        [3, 4, 5, 2, 8, 6, 1, 7, 9]
    ]

    board1_status = check_sudoku(board1)
    board2_status = check_sudoku(board2)

    if board1_status is False:
        print('%s is not a valid board' % board1)
    else:
        print('%s is a valid board' % board1)

    if board2_status is False:
        print('%s is not a valid board' % board2)
    else:
        print('%s is a valid board' % board2)
main_q7()
