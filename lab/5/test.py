def count_chars():
	a_str = input('Please enter a string: ')
	a_char = input('Please enter a letter: ')
	for_occurence = 0
	while_occurence = 0
	for x in a_str:
		if a_char == x:
			for_occurence += 1
	print('For')
	print('The letter %s appears %s times' % (a_char, for_occurence))

	end = False
	x = 0
	while end is not True:
		if a_str[x] == a_char:
			while_occurence += 1
		x += 1
	print('While')
	print('The letter %s appears %s times' % (a_char, while_occurence))
count_chars()
