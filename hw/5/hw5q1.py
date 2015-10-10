num = int(input('Please enter a positive integer: '))
count = 0
index = 0
while count < num:
	if index % 2 == 1:
		print(index)
		count += 1
	index += 1
