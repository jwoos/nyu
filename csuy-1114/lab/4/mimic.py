import math


def mimic_atan():
	a = int(input('Please enter a non-zero number: '))
	b = int(input('Please enter a non-zero number: '))
	vector = math.hypot(a, b)
	if a > 0 and b > 0:
		# first quadrant
		print(math.atan(vector))
	elif a > 0 and b < 0:
		# second quadrant
		print(math.atan(vector))
	elif a < 0 and b < 0:
		# third quadrant
		print(math.atan(vector))
	elif a < 0 and b > 0:
		# fourth quadrant
		print(math.atan(vector))
	else:
		print('You entered a zero!')
	
	print(math.atan2(b, a))
mimic_atan()
