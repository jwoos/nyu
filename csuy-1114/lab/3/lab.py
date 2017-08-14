import math
from turtle import *


def romanize():
	num = int(input('Please input a number less than 100 to convert to roman numerals: '))
	roman_num = []
	hundred = 0
	fifty = 0
	ten = 0
	five = 0
	one = 0

	if num > 100:
		print('Please enter a number less than 100')
		romanize()
	else:
		hundred = num // 100
		fifty = num // 50
		ten = (num - fifty * 50) // 10
		five = (num - (fifty * 50) - (ten * 10)) // 5
		one = (num - (fifty * 50) - (ten * 10) - (five * 5)) // 1

	for _ in range(hundred):
		roman_num.append('C')

	for _ in range(fifty):
		roman_num.append('L')

	for _ in range(ten):
		roman_num.append('X')

	for _ in range(five):
		roman_num.append('V')

	for _ in range(one):
		roman_num.append('I')

	print(''.join(roman_num))
romanize()


def check_right():
	sides = input('Please input three numbers separated by a comma to check if it\'s a right triangle: ')
	sides_list = sides.split(',')
	sides_int_list = []
	for x in sides_list:
		sides_int_list.append(int(x))
	max_num = max(sides_int_list)
	max_num_index = sides_int_list.index(max_num)
	del [max_num_index]
	if math.hypot(sides_int_list[0], sides_int_list[1]) == max_num:
		print('It\'s a right trianlge')
	else:
		print('It\'s not a right triangle')
check_right()


def draw_two():
	setup(100, 100)
	pendown()
	forward(100)
	right(90)
	forward(50)
	right(90)
	forward(100)
	left(90)
	forward(50)
	left(90)
	forward(100)
	penup()
draw_two()


def linear():
	a = int(input('Please enter the first digit: '))
	b = int(input('Please enter the second digit: '))

	if a == 0 and b == 0:
		print('Infinite solution')
	else:
		solution = (0 - b) / a
		print('x = %s' % solution)
linear()


def draw_rect():
	a_width = int(input('Please enter a width between 50 and 500, exclusive: '))
	b_height = int(input('Please enter a height between 50 and 500, exclusive: '))

	if a_width == b_height:
		print('A and B can\'t be the same, try again')
		draw_rect()
	elif a_width >= 500 or b_height >= 500:
		print('Both  A and B have to be less than 500')
		draw_rect()
	elif a_width <= 50 or b_height <= 50:
		print('Both A and B have to be greater than 50')
		draw_rect()
	else:
		setup(750, 750)
		speed(3)
		pendown()
		forward(a_width)
		right(90)
		forward(b_height)
		right(90)
		forward(a_width)
		right(90)
		forward(b_height)
		right(90)

		goto(a_width/2, 0)
		goto(a_width, -b_height/2)
		goto(a_width/2, -b_height)
		goto(0, -b_height/2)
		goto(a_width/2, 0)
		penup()
draw_rect()
