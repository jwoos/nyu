import math

product = 1
length = 0
multiply_by_this = input('Please enter a positive integer: ')

while multiply_by_this != 'Done':
	length += 1
	product *= int(multiply_by_this)
	multiply_by_this = input('Please enter a positive integer: ')

print('The geometric mean is %s' % (round(math.pow(product, (1 / length)), 4)))
