import random

def count(lst, item):
	count = 0
	for i in lst:
		if i == item:
			count += 1
	return count

def find_min_index(lst):
	minimum = lst[0]
	for i in lst:
		if i < minimum:
			minimum = i
	return lst.index(minimum)

def circular_shift_list(lst, k):
	solution = lst[k::] + lst[0:k:]
	return solution

def get_common_elem (list1, list2):
	solution = []
	for x in list1:
		if x in list2:
			solution.append(x)
	return solution

def bulls_cows():
	num = []
	for _ in range(4):
		num.append(str(random.randint(0,9)))
	print(num)

	correct = False
	tries = 0

	while correct == False:
		cows = 0
		bulls = 0
		user = input('Try to guess the number: ')

		if ''.join(num) == user:
			correct = True
			print('You got it!')
			print('You took %s tries' % tries)
		else:
			for i in range(len(num)):
				if num[i] == user[i]:
					bulls += 1
				elif user[i] in num:
					cows += 1
			print('There are %s bulls and %s cows' % (bulls, cows))
			tries += 1
bulls_cows()
