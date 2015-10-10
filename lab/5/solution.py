import turtle


def make_shapes():
	num = int(input('Please enter an integer: '))
	for x in range(1, num + 1):
		the_asterisk = '*' * x * 2
		the_asterisk = the_asterisk[:-1:]
		print(the_asterisk)
	num = int(input('Please enter an integer: '))
	for i in range(num):
		print('#' * (i) + '%' + '$' * (num - i - 1))
make_shapes()


def count_chars():
	a_str = input('Please enter a string: ')
	a_char = input('Please enter a letter: ')
	for_occurence = 0
	while_occurence = 0
	for x in a_str:
		if a_char == x:
			for_occurence += 1
	print('For')
	print('The letter %s appears %s times' % (a_char, for_occurence))

	x = 0
	while x < len(a_str):
		if a_str[x] == a_char:
			while_occurence += 1
		x += 1
	print('While')
	print('The letter %s appears %s times' % (a_char, while_occurence))
count_chars()


def draw_shape():
	side_num = int(input('Please enter a positive integer: '))
	total_angle = 180 * (side_num - 2)
	turtle.setup(500, 500)
	turtle.pendown()

	for x in range(side_num):
		turtle.forward(100)
		turtle.left(180 - (total_angle / side_num))
	turtle.penup()
draw_shape()


def extra():
	positive_int = int(input('Please enter a positive integer: '))
	for x in range(1, positive_int):
		if x ** 3 < positive_int:
			print(x ** 3)

	up_to = int(input('Please enter another positive integer: '))
	cubed_sum = 0
	index = 1
	while index <= up_to:
		cubed_sum += index ** 3
		index += 1
	print(cubed_sum)
extra()
