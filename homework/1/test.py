import time
import random
from selection import selectionSort
from quicksort import quickSort
from insertion import insertionSort
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib.ticker as mticks

import numpy as np

import sys
sys.setrecursionlimit(1000000)

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

def generate_numbers():
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
    return total

    # f = open(method + '-times.txt', 'a')
    # f.write(str(len(num_list)) + ',' + str(total) + '\n')
    # f.close()

def test_average(length, count, sorted='random'):
    f = open('numbers/' + sorted + '/' + str(length) + '.txt', 'r')
    numbers = f.readline().split(',')
    numbers.pop()

    for x in range(len(numbers)):
        numbers[x] = int(numbers[x])

    selection_total = 0
    quick_total = 0
    insertion_total = 0

    for _ in range(count):
        selection_total += test(numbers, 'selection')
    selection_average = selection_total / count
    print('selection')
    print('length: %s, count: %s, average: %s \n' % (length, count, selection_average))
    for _ in range(count):
        quick_total += test(numbers, 'quick')
    quick_average = quick_total / count
    print('quick')
    print('length: %s, count: %s, average: %s \n' % (length, count, quick_average))
    for _ in range(count):
        insertion_total += test(numbers, 'insertion')
    insertion_average = insertion_total / count
    print('insertion')
    print('length: %s, count: %s, average: %s \n' % (length, count, insertion_average))

    f.close()

    w = open('results/' + sorted + '/' + str(length) + '.txt', 'w')
    w.write(str(selection_average) + '\n')
    w.write(str(quick_total) + '\n')
    w.write(str(insertion_total) + '\n')
    w.close()

def test_all():
    lengths = [10, 25, 50, 100, 250, 500, 1000, 2500, 5000, 10000, 25000]
    for length in lengths:
        test_average(length, 1, sorted='random')
    for length in lengths:
        test_average(length, 1, sorted='ascending')
    for length in lengths:
        test_average(length, 1, sorted='descending')

def graph(sorted="random"):
    lengths = [10, 25, 50, 100, 250, 500, 1000, 2500, 5000, 10000, 25000]
    selection = []
    quick = []
    insertion = []

    for length in lengths:
        f = open('results/' +  sorted + '/' + str(length) + '.txt', 'r')
        line = f.readline().strip()
        selection.append(line)
        line = f.readline().strip()
        quick.append(line)
        line = f.readline().strip()
        insertion.append(line)
        f.close()

    print(len(lengths))
    print(len(selection))

    selection = np.array(selection)
    quick = np.array(quick)
    insertion = np.array(insertion)
    lengths = np.array(lengths)

    fix, ax = plt.subplots()
    ax.xaxis.set_major_locator(mticks.MultipleLocator(1000))
    ax.yaxis.set_major_locator(mticks.MultipleLocator(0.5))
    selection_plot = plt.plot(lengths, selection, '-ro', label='selection sort')
    quick_plot = plt.plot(lengths, quick, '-bo', label='quick sort')
    insertion_plot = plt.plot(lengths, insertion, '-go', label='insertion sort')
    plt.xlabel('Length of number list')
    plt.ylabel('Time (s)')
    plt.title('Runtime for sorting algorithms visualized on a linear scale')
    plt.legend()
    plt.rcParams.update({'font.size': 26})
    plt.show()

    fix, ax = plt.subplots()
    ax.xaxis.set_major_locator(mticks.MultipleLocator(1000))
    ax.yaxis.set_major_locator(mticks.MultipleLocator(0.5))
    plt.xscale('log')
    plt.yscale('log')
    selection_plot = plt.plot(lengths, selection, '-ro', label='selection sort')
    quick_plot = plt.plot(lengths, quick, '-bo', label='quick sort')
    insertion_plot = plt.plot(lengths, insertion, '-go', label='insertion sort')
    plt.xlabel('Length of number list')
    plt.ylabel('Time (s)')
    plt.title('Runtime for sorting algorithms visualized on a logarithmic scale')
    plt.legend()
    plt.rcParams.update({'font.size': 26})
    plt.show()

# graph(sorted='random')
# graph(sorted='ascending')
graph(sorted='descending')
