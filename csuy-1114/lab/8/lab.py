def fib(n):
	current_num = 1
	previous_num = 1
	index = 3
	while index != n:
		temp = current_num
		current_num += previous_num
		previous_num = temp
		index += 1
		print(previous_num)
		print(current_num)
	if index == n:
		return current_num

nth = int(input('Please enter a number: '))
nth_fib = fib(nth)
print('The %s-th Fibonacci number is %s' % (nth, nth_fib))


def find(some_string, sub_string, start, end):
	if sub_string in some_string:
		new_string = some_string[start:end:]
		index = new_string.index(sub_string)
		index += start
		return index
	else:
		return -1
