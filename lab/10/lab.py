import random


def remove_below_avg(lst):
	lst_sum = 0
	for x in lst:
		lst_sum += x
	avg = lst_sum / len(lst)
	solution = []
	for index in range(len(lst)):
		if lst[index] >= avg:
			solution.append(lst[index])
	return solution

print(remove_below_avg([2, 3, 5, 1, -4, 8, 0, -1]))


def generate_state():
	lst = ['rock', 'paper', 'scissors']
	state = lst[random.randint(0, 2)]
	return state


def who_won(user_state, comp_state):
	if (user_state == 'paper' and comp_state == 'paper') or (user_state == 'scissors' and comp_state == 'scissors') or (user_state == 'rock' and comp_state == 'rock'):
		return 'tie'
	elif (user_state == 'rock' and comp_state == 'scissors') or (user_state == 'scissors' and comp_state == 'paper') or (user_state == 'paper' and comp_state == 'rock'):
		return 'person'
	elif (user_state == 'rock' and comp_state == 'paper') or (user_state == 'scissors' and comp_state == 'rock') or (user_state == 'paper' and comp_state == 'scissors'):
		return 'computer'


def one_game():
	user_state = input('Please enter rock, paper or scissors: ').lower()
	comp_state = generate_state()
	print('User choice: %s' % user_state)
	print('Computer coice: %s' % comp_state)
	return user_state, who_won(user_state, comp_state)


def forever():
	play_state = ''
	while play_state != 'done':
		game_state = one_game()
		win_state = game_state[1]
		play_state = game_state[0]
		if win_state == 'tie':
			print('It is a tie')
		elif win_state == 'person':
			print('The user wins')
		elif win_state == 'computer':
			print('The computer wins')
forever()
