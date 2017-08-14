import random

comp_num = random.randint(0, 100)
solved = False
print('I thought of a number between 1 and 100! Try to guess it')
while solved is False:
	guess = int(input('Try to guess what it is: '))
	if guess < comp_num:
		print('Wrong guess. My number is bigger than yours')
	elif guess > comp_num:
		print('Wrong guess. My number is smaller than yours')
	elif guess == comp_num:
		print('Congrats! You guessed my number')
		solved = True
