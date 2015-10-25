one_zero = input('Please enter a string of 1s and 0s: ')
end = False
index = 0

while index < len(one_zero):
	state = one_zero[index]
	count = 0

	while index < len(one_zero) and state == one_zero[index]:
		count += 1
		index += 1
	
	if state == '0':
		print(count, '0\'s')
	else:
		print(count, '1\'s')
