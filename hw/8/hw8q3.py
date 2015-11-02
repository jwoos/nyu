'''

Name: Junwoo Shin
NetID: JS8460
Filename: hw8q3.py

Explanation
-----------
First the make_shapes() method was taken from my initial code from the lab. I just added a parameter for shift and used it to add the shift.
in n_triangles, it loops over the range of the number of triangles and since the nth triangle has n + 1 number of rows. The shift has to decrease by x to compensate for the natural right shift as the triangle gets bigger.

'''


def make_shapes(num, char, shift):
	for x in range(1, num + 1):
		print(' ' * (shift) + ' ' * (num - x) + char * (x * 2 - 1) + ' ' * (num - x))

def n_triangles(amount, shift, char):
	for x in range(1, amount + 1):
		make_shapes(x + 1, char, shift - x)


def main():
	amount = int(input('How many triangles should be generated: '))
	shift = int(input('How much should they be shifted by: '))
	char = input('Enter a character to use: ')

	n_triangles(amount, shift, char)

if __name__ == '__main__': main()
