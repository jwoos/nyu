import time
import random
from selection import selectionSort
from quicksort import quickSort
from insertion import insertionSort
import matplotlib.pyplot as plt

def generate_list(length, filename, sorted='random'):
    f = open(filename, 'a')
    if sorted == 'random':
        for _ in range(length):
            f.write(str(random.randint(-1000000, 1000000)) + ',')
        f.write('\n')
    elif sorted == 'ascending':
        for x in range(length):
            f.write(str(x * 2) + ',')
    elif sorted == 'descending':
        for x in range(length):
            f.write(str(-(x * 2)) + ',')
    f.close()

def test(num_list, method):
    to_use = {
        'selection': selectionSort,
        'quick': quickSort,
        'insertion': insertionSort
    }

    start = time.time()
    to_use[method](num_list)
    end = time.time()

    total = end - start
    print(total)

    f = open(method + '-times.txt', 'a')
    f.write(str(len(num_list)) + ',' + str(total) + '\n')
    f.close()


lengths = [10, 25, 50, 100, 250, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000, 250000, 500000, 1000000, 2500000, 5000000, 10000000]
for length in lengths:
    print(length)
    start = time.time()
    # generate_list(length, 'numbers/random/' + str(length) + '.txt', sorted='random')
    # generate_list(length, 'numbers/ascending/' + str(length) + '.txt', sorted='ascending')
    generate_list(length, 'numbers/descending/' + str(length) + '.txt', sorted='descending')
    end = time.time()
    total = end - start
    print(total)
    print()
