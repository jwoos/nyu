'''

Name: Junwoo Shin
NetID: JS8460
Filename: hw7q4.py

Explanation
-----------
I had to make use of two for loops. In each iteration of the outer loop, it would reset the count to 0, count either the 1's or 1's and then print them.
The inside was critical as it would count the number in a row while the outside made sure it reached the end.

'''

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
