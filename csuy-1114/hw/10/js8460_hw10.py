import random

# Question 1
def create_permutation(lst):
	random.shuffle(lst)
	return lst
	
def main_q1():
	plus_int = int(input('Please enter a positive integer: '))
	num_list = [x for x in range(1, plus_int + 1)]
	shuffled = create_permutation(num_list)
	print(shuffled)
main_q1()

# Question 2
def add_list(lst1, lst2):
	solution = []
	for index in range(len(lst1)):
		solution.append(lst1[index] + lst2[index])
	return solution

def main_q2():
	lst1 = []
	input1 = 0
	print('Enter the first list of numbers')
	while input1 != 'done':
		input1 = input('Enter a number: ')
		if input1 != 'done':
			lst1.append(int(input1))
	print('Enter the second list of numbers')
	
	lst2 = []
	input2 = 0
	while input2 != 'done':
		input2 = input('Enter a number: ')
		if input2 != 'done':
			lst2.append(int(input2))

	if len(lst1) == len(lst2):
		the_sum_list = add_list(lst1, lst2)
		for x in the_sum_list:
			print(x)
	else:
		print('The lists are different lengths!')
main_q2()

# Question 3
def create_prefix_list(lst):
	big_list = []
	for index in range(len(lst) + 1):
		big_list.append(lst[0:index:])
	return big_list

def main_q3():
	the_list = [2, 4, 6, 8, 10]
	prefixed = create_prefix_list(the_list)
	print('The list was %s and the list of prefixes is %s' % (the_list, prefixed))
main_q3()

# Question 4
def read_menu():
	item_count = int(input('How many items are on the menu?'))
	menu = []
	for _ in range(item_count):
		name_price = input('Enter item in the form NAME:PRICE \n')
		menu.append(tuple(name_price.split(':')))
	return menu

def read_customer_order():
	order_list = []
	order = ''
	while order != 'done':
		order = input('What would you like to order?')
		if order != 'done':
			order_list.append(order)
	return order_list

def compute_price(menu_list, order_list):
	price = 0
	for order_item in order_list:
		for menu_item in menu_list:
			if order_item == menu_item[0]:
				price += int(menu_item[1])
	return price

def main_q4():
	for i in range(1, 4):
		print('Person %s' % i)
		menu = read_menu()
		order = read_customer_order()

		price = compute_price(menu, order)
		tax = price * 0.085
		tip = price * 0.15
		total = tax + tip + price
		print('The total is %s \n' % total)
main_q4()
