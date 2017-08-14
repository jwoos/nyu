'''

Name: Junwoo Shin
NetID: JS8460
Filename: hw8q1.py

Explanation
-----------
First I printed the days at the top which would have been less expensive looping over a tuple.
The optional parameter end was used to allow printing on same line with even space. 
I first printed the spaces based on what day it started. After that I print the first line of numbers. If it's one digit I right align by checking if it's only one digit and adding a space at the front if it is.
After the first line of numbers were printed I did repeated the same thing for the second and looped over in series of 7's. It would continue right until day_current was greater than day_count.
I made it return the calendar return on the index it stopped on and used that same index to to run the calendar again in the loop over the months array.

'''

def calendar(day_count, day_start):
	day_current = 1

	# Print the top
	days = ['Mo', 'Tu', 'We', 'Th', 'Fr', 'Sa', 'Su']
	for day in days:
		print(day, end='\t')
	print('')
	
	# Print spaces to offset start
	if day_start != 1:
		for spaces in range(day_start - 1):
			print('', end='\t')
			day_current = spaces

	# First row
	for first_row in range(1, 7 - day_start + 2):
		if len(str(first_row)) != 2:
			print(' ' + str(first_row), end='\t')
		elif day_current <= day_count:
			print(first_row, end='\t')
		day_current = first_row
	day_current += 1
	print('')
	
	# Until current day is greater than number of days print the numbers counting up
	while day_current <= day_count:
		for current_index in range(7):
			if len(str(day_current)) != 2:
				print(' ' + str(day_current), end='\t')
			elif day_current < day_count:
				print(day_current, end='\t')
			elif day_current == day_count:
				print(day_current)
				return current_index + 2
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

def calendar_year(year, start):
	months = [
		['January', 31],
		['February', 28], 
		['March', 31], 
		['April', 30], 
		['May', 31], 
		['June', 30], 
		['July', 31],
		['August', 31], 
		['September', 30],
		['October', 31], 
		['November', 30],
		['December', 31]
	]

	# If the year is a leap year change number of days for february into 29
	if leapyear(year):
		months[1] = 29
	
	for month in months:
		print('\t\t%s %s' % (month[0], year))
		start = calendar(month[1], start)
		print('')

def main():
	year = int(input('Please enter the year: '))
	day_start = int(input('What day does it start on: '))

	calendar_year(year, day_start)

if __name__ == '__main__': main()
