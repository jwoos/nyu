f = open('sample.csv', 'r')
line = f.read().split('\n')
for x in line:
	print(x.split(','))
