rows = 5
columns = 10

for exponent in range(1, rows + 1):
    for base in range(1, columns + 1):
        print(base**exponent, end='\t')
    print()
