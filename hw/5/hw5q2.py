num = int(input('Please enter a positive integer: '))

for row in range(1, num * 2 + 1):
	if row <= num:
		new_row = num - row + 1
		print(' ' * (row - 1) + '*' * (new_row * 2 - 1) + ' ' * (row - 1))
	else:
		new_row = row - num
		print(' ' * (num - new_row) + '*' * (new_row * 2 - 1) + ' ' * (num - new_row))
