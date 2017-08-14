import math

length = int(input('Please enter the length of the sequence: '))
product = 1
for _ in range(length):
	multiply_by_this = int(input('Please enter a positive integer: '))
	product *= multiply_by_this
print('The geometric mean is %s' % (round(math.pow(product, (1 / length)), 4)))
