import math
odd_string = input('Please enter a string with odd number of characters: ')

if len(odd_string) % 2 == 1:
  middle = math.floor(len(odd_string)/2)
  # Print the middle character
  print(odd_string[middle])
  # Print up to middle
  print(odd_string[:middle:])
  # Print from middle to end
  print(odd_string[middle + 1::])
else:
  print('It has even number of characters, try again')
