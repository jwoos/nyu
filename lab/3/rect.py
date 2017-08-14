from turtle import *


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
