import turtle
import math


def phone_number():
	old_phone = input('Please enter the phone number: ')
	old_phone_temp = '718-260-'
	new_phone_temp = '646-997-'

	if old_phone[:8:] == old_phone_temp:
		print('The new number is', new_phone_temp + old_phone[8::])
	else:
		print('That is not a valid SoE number')
phone_number()


def draw_shapes():
	color = input('Please enter a color (red/green/blue): ')
	shape = input('Please enter a shape (triangle/square): ')
	size = int(input('Please enter a size: '))

	turtle.setup(500,500)
	turtle.pendown()
	turtle.color(color)
	if shape == 'square':
		for _ in range(4):
			turtle.forward(size)
			turtle.left(90)
	elif shape == 'triangle':
		for _ in range(3):
			turtle.forward(size)
			turtle.left(120)
draw_shapes()


def str_stuff():
	three_word = input('Please enter a three word phrase: ')
	for x in three_word.split(' '):
		print(x[0])
	one_word = input('Please enter a word: ')
	print(one_word.upper())
	three_letter = input('Please enter a three letter word: ')
	for y in three_letter:
		print(ord(y))
str_stuff()


def check_password():
	password = input('Please enter the password: ')
	has_upper = False
	for i in password:
		if i.isupper():
			has_upper = True
	if len(password) >= 6 and has_upper:
		print('The password is valid')
	else: 
		print('The password is not at least 6 characters long or it doesn\'t have an uppercase letter')
check_password()


def string_operation():
	num_str = input('Please enter two numbers separated by a space: ')
	num_1 = int(num_str.split(' ')[0])
	num_2 = int(num_str.split(' ')[1])
	print('%s + %s = %s' % (num_1, num_2, num_1 + num_2))
string_operation()


def check_int():
	check_this = input('Please enter a string to check if it is an integer: ')
	if check_this.isdigit() or check_this.isnumeric() or check_this.isdecimal():
		print('The string is an integer')
	else:
		print('It is not an integer')
check_int()


def mimic_atan():
	a = int(input('Please enter a non-zero number: '))
	b = int(input('Please enter a non-zero number: '))
	vector = hypot(a, b)
	if a > 0 and b > 0:
		# first quadrant
		math.atan(vector)
	elif a > 0 and b < 0:
		# second quadrant
		math.atan(vector)
	elif a < 0 and b < 0:
		# third quadrant
		math.atan(vector)
	elif a < 0 and b > 0:
		# fourth quadrant
		math.atan(vector)
	else:
		print('You entered a zero!')
