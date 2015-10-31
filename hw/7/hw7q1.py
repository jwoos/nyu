'''

Name: Junwoo Shin
NetID: JS8460
Filename: hw7q1.py

Explanation
-----------
First I checked to see if the character was lowercase or uppercase as it would affect how it was handled.
After it was check the ord() metho was used on it to obtain the numerical value and subtracted by ord('a') for lower case and ord('A') for uppercase.
That forces the numerical values to fall within the range of 1-26 which correspond to each letter of the alphabet. 
That value was then taken and the shift was added to it and the sum was modded by 26. This got rid of any potential cases where the sum would go past 26 in which case it would start form 1 again.
Then ord('a') was added for lowercase letters and ord('A') for uppercase to get back to the original range and chr() was applied to it which resulted in the shifted character.
The character was then concatenated onto a previously set string and when the loop was finished printed the string.

'''

string = input('Please enter a string: ')
shift = int(input('How much should it be shifted by? '))

encoded = ''

for letter in string:
    if letter == ' ':
        encoded += letter
    elif letter.islower():
        letter_ord = ord(letter) - ord('a')
        shifted = (letter_ord + shift) % 26
        encoded += chr(shifted + ord('a')) 
    elif letter.isupper():
        letter_ord = ord(letter) - ord('A')
        shifted = (letter_ord + shift) % 26
        encoded += chr(shifted + ord('A')) 
    else:
        encoded += letter

print('Encrypted string is', encoded)
