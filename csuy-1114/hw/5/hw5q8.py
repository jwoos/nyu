positive_int = int(input('Please enter a positive integer: '))
for row in range(1, positive_int + 1):
	row_num = []
	print(' ' * (positive_int - row), end='')
	for num in range(1, row + 1):
		print(num, end='')
	print('')
