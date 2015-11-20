import random


def write_name(filename, first_name, last_name):
	f = open(filename, 'w')
	f.write(first_name + ' ' + last_name + '\n')
write_name('text.txt', 'Junwoo', 'Shin')


def write_rand_numbers(filename, n):
	f = open(filename, 'w')
	for line in range(n):
		f.write(str(random.randint(1, 100)) + '\n')
write_rand_numbers('text2.txt', 100)


def sum_column(filename):
	f = open(filename, 'r')
	num_list = []
	for a_num in f:
		print(a_num)
		num_list.append(int(a_num.strip()))
	total = 0
	for x in num_list:
		total += x
	print(total)
sum_column('text2.txt')


def write_table(filename):
	f = open(filename, 'r')

	print('<!DOCTYPE html>')
	print('<html>\n')
	print('<table>')
	table = []

	header = f.readline().split(',')
	header[-1] = header[-1].strip()
	table.append(header)

	for row in f:
		temp = row.split(',')
		temp[-1] = temp[-1].strip()
		table.append(temp)
	print(table)
	for row in table:
		print('\t' + '<tr>')
		for elem in row:
			print('\t' * 2 + '<td>' + elem + '</td>')
		print('\t' + '</tr>')
	print('</table>')
	print('</html>')


write_table('samplefile.csv')
