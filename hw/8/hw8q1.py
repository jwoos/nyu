'''

Name: Junwoo Shin
NetID: JS8460
Filename: hw8q1.py

Explanation
-----------
First I printed the days at the top which would have been more concise looping over a tuple and printing.
The optional parameter end was used to allow printing on same line with even space. 
I first printed the spaces based on what day it started. After that I print the first line of numbers. If it's one digit I right align by checking if it's only one digit and adding a space at the front if it is.
After the first line of numbers were printed I did repeated the same thing for the second and looped over in series of 7's. It would continue right until day_current was greater than day_count.


'''

def calendar(day_count, day_start):
	day_current = 1

	print('Mo', end='\t')
	print('Tu', end='\t')
	print('We', end='\t')
	print('Th', end='\t')
	print('Fr', end='\t')
	print('Sa', end='\t')
	print('Su')

	for spaces in range(day_start - 1):
		print('', end='\t')
		day_current = spaces

	for first_row in range(1, 7 - day_start + 2):
		if len(str(first_row)) != 2:
			print(' ' + str(first_row), end='\t')
		elif day_current <= day_count:
			print(first_row, end='\t')
		day_current = first_row
	day_current += 1
	print('')

	while day_current <= day_count:
		for current_index in range(7):
			if len(str(day_current)) != 2:
				print(' ' + str(day_current), end='\t')
			elif day_current < day_count:
				print(day_current, end='\t')
			elif day_current == day_count:
				print(day_current)
				return current_index + 1, current_index + 2
			day_current += 1
		print('')

def leapyear(year):
	if year % 4 == 0:
		if year % 100 == 0 and year % 400 == 0:
			return True
		elif year % 100 == 0 and year % 400 != 0:
			return False
		else:
			return True
	else:
		return False

def main():
	
