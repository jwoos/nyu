import math

sides = [0, 0, 0]
sides[0] = int(input('Please enter side one of the triangle: '))
sides[1] = int(input('Please enter another side of the triangle: '))
sides[2] = int(input('Please enter the last side of the triangle: '))

if sides[0] == sides[1] == sides[2]:
	print('It is an equilateral triangle')
elif sides[0] == sides[1] or sides[0] == sides[2] or sides[1] == sides[2]:
	max_num = max(sides)
	max_num_index = sides.index(max_num)
	del sides[max_num_index]
	if math.hypot(sides[0], sides[1]) == max_num:
		print('It is an isosceles right trianlge')
	else:
		print('It is an isosceles triangle')
else:
	print('It is not isosceles or equilateral')
