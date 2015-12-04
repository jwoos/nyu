def add_entry(phonebook, name, phonenumber):
	if len(phonenumber) == 10:
		try:
			int(phonenumber)
			phonebook[name] = phonenumber
		except ValueError:
			print('Invalid phone number')
	else:
		print('Invalid phone number')
	return phonebook

def lookup(phonebook, name):
	return phonebook[name]

def print_all(phonebook):
	for key in phonebook:
		print('name: %s | phone number: %s' % (key, phonebook[key]))

def main():
	f = open('phonebook.txt')
	phonebook = {}
	for line in f:
		line = line.split(' ')
		last = line[0][:-1:]
		first = line[1]
		number = line[2].rstrip()
		
		add_entry(phonebook, ' '.join([first, last]), number)
	
	print_all(phonebook)
main()

def myfunc():
	try:
		x = int(input('Please enter a number: '))
		y = int(input('Please enter another number: '))
		try:
			print(x / y)
		except ArithmeticError:
			print('infinity')
	except ValueError:
		print('Input must be numbers!')
	
myfunc()
