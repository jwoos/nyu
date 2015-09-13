"""
name = input('What\'s your name? \n')
print('Your name is %s' % name)
"""

"""
first = int(input('Please put in the first number: '))
second = int(input('Please put in the second number: '))


def operations(first, second):
	print('The sum is %s, the product is %s, and the difference is %s' % (first + second, first * second, first - second))

operations(first, second)
"""

temp = int(input('Please put in the temperature in Farenheit: '))


def convert(temp):
	print('The temperature in Celcius is: ' + str((temp - 32) * 5 / 9))

convert(temp)
