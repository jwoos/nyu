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
