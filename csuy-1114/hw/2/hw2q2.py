number = input('Please input a three digit positive integer: ')
solution = 0

for x in number:
	solution += int(x)

print('The sum of the digits is: %s' % solution)
