english_word = input('Please enter a word: ')

vowels = ('a', 'e', 'i', 'o', 'u')

# Count vowels by comparing it to tuple
vowel_count = 0
for x in english_word:
  if x in vowels:
    vowel_count += 1

consonant_count = len(english_word) - vowel_count

print('%s has %s vowels and %s consonants' % (english_word, vowel_count, consonant_count))
