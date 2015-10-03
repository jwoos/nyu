password = input('Please enter an input: ')

upper_count = 0
lower_count = 0
digit_count = 0
special_count = 0

# check if length is greater than 8 first, otherwise end
if len(password) >= 8:
  # count each type of character
  for x in password:
    if x.isupper():
      upper_count += 1
    elif x.islower():
      lower_count += 1
    elif x.isdigit():
      digit_count += 1
    else:
      special_count += 1
  
  if upper_count >= 2 and lower_count >= 1 and digit_count >= 2 and special_count >= 1:
    print('%s is a valid password' % password)
  else:
    print('%s is not a valid password' % password)
else:
  print('%s is not a valid password' % password)
