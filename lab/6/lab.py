def factorial():
	positive_int = int(input('Please enter a positive integer: '))
	factorial_prod = 1
	for num in range(1, positive_int + 1):
		factorial_prod *= num
	print('The factorial of %s is %s' % (positive_int, factorial_prod))
factorial()


def convert_case():
	a_str = input('Please enter a string: ')
	converted_str = ''
	for a_char in a_str:
		if a_char.isupper():
			print(a_char.lower(), end='')
		elif a_char.islower():
			print(a_char.upper(), end='')
	print('\n', end='')
convert_case()
