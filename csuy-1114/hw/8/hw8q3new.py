'''

Name: Junwoo Shin
NetID: JS8460
Filename: hw8q3.py

Explanation
-----------
First I use the print_shifted_triangle to make the actual triangle. I pass in the shift because i noticed that it was equal to number of rows - 1. I looped over the range of number of triangles and passed in the margin to make the triangle align at the center. 

'''

def print_shifted_triangle(n, m, symbol):
	for x in range(1, n + 1):
		print(' ' * (m) + ' ' * (n - x) + symbol * (x * 2 - 1))

def print_pine_tree(n, symbol):
	for x in range(n):
		m = n - x + 1
		print_shifted_triangle(x + 2, m, symbol)

def main():
	amount = int(input('How many triangles would you like? \n'))
	symbol = input('What would you like it to be made up of? \n')
	print()
	print_pine_tree(amount, symbol)

if __name__ == '__main__':
	main()
