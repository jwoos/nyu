a_char = input('Please enter a character: ')

# Using string methods
if a_char.islower():
  print('%s is a lower case letter' % a_char)
elif a_char.isupper():
  print('%s is an upper case letter' % a_char)
elif a_char.isdigit():
  print('%s is a digit' % a_char)
else:
  print('%s is a non-alphanumeric character' % a_char)

# Without string methods
a_char_ord = ord(a_char)
if 97 <= a_char_ord <= 122:
    print('%s is a lower case letter' % a_char)
elif 65 <= a_char_ord <= 90:
    print('%s is an upper case letter' % a_char)
elif 48 <= a_char_ord <= 57:
    print('%s is a digit' % a_char)
else:
    print('%s is a non-alphanumeric character' % a_char)
