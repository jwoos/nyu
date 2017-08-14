num = input('Please enter a positive integer: ')
for index in range(1, int(num) + 1):
	even_count = 0
	odd_count = 0
	for digit in str(index):
		if int(digit) % 2 == 0:
			even_count += 1
		elif int(digit) % 2 == 1:
			odd_count += 1
	if even_count > odd_count:
		print(index)
