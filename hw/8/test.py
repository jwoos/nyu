def make_shapes(num, char):
	for x in range(1, num + 1):
		print(' ' * (num - x) + char * (x * 2 - 1) + ' ' * (num - x))
make_shapes(10, '*')
