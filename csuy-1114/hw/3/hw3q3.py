import math

a = int(input('Please enter a: '))
b = int(input('Please enter b: '))
c = int(input('Please enter c: '))

if a == 0 and b == 0 and c == 0:
	print('There are an infinite number of solutions')
elif a == 0 and b == 0:
	print('There is no solution')
elif b == 0 :
	print('There are no real solutions')
else:
	discriminant = (b ** 2) - (4 * a * c)
	solution = []
	if math.sqrt(discriminant) == 0:
		solution.append(-b/ 2 * a) 
		print('There is one solution and it is %s' % (solution[0]))
	elif math.sqrt(discriminant) < 0:
		print('There are no solutions')
	else:
		solution.append((-b + math.sqrt(discriminant)) / (2 * a))
		solution.append((-b - math.sqrt(discriminant)) / (2 * a))
		print('There are two solutions and they are %s and %s' % (solution[0], solution[1]))
