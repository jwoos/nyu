a_str = input('Please enter a string with only lowercase letters: ')
increasing = True
index = 0
while index < len(a_str) - 1:
	if not (a_str[index] < a_str[index + 1]):
		increasing = False
	index += 1
if increasing is True:
	print('It is increasing')
else: 
	print('It is not increasing')
