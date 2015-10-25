import random

random_int = random.randint(1, 100)
guesses_left = 5
solved = False

beg_range = 1
end_range = 100

print('I thought of a number between %s and %s! Try to guess it' % (beg_range, end_range))
while solved is False:
    if guesses_left == 0:
        print('Sorry, you used all your guesses')
        break
    else:
        guess = int(input('Try to guess what it is: '))
        guesses_left -= 1
        if guess == random_int:
            print('Congrats! You guessed my number in %s guesses' % (guesses_left))
        elif guess < random_int:
            beg_range = guess
            print('Wrong guess! Guess in range %s and %s. You have %s more chances' % (beg_range, end_range, guesses_left))
        elif guess > random_int:
            end_range = guess
            print('Wrong guess! Guess in range %s and %s. You have %s more chances' % (beg_range, end_range, guesses_left))
