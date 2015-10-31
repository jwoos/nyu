'''

Name: Junwoo Shin
NetID: JS8460
Filename: hw7q3.py

Explanation
-----------
I imported the random module, which would allow me to generate (pseudo) random numbers. I specified the min and max and set it to a variable. I then set beg_rane and end_range to allow modifying the range that the computer prints. Two cases would end the while loop, if the guesses_left was 0 or the user guessed it correctly and solved becomes True.
Each guess would subtract a guess left and in the case they were wrong the computer would print a new range using the user's input.
It's basically saying either that the number was bigger or the number was smaller. So I compared the guess to the integer the program generated and if the guess is smaller, the beg_range is modified while if the guess it larger, the end_range is modified.

'''

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
