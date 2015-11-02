'''

Name: Junwoo Shin
NetID: JS8460
Filename: hw8q2.py

Explanation
-----------
In the first method in the occurrence of the first space it will stop adding letters to the word variable and return the variable. Spaces indicate the completion of a word.
Using the same logic for the second function the index was used to get the first occurrence of a space. The index was then used to slice and return the string without the first word.
To reverse it, I use two for loops where I iterate over two loops using the first one to decrease the second one. The second loop determines how many times the first word is removed and since it's getting smaller more of the original words remain towards the end. This allows the use of the first method to get the word and add it to final_string.
When both loops finish it will return the reversed string

'''


def get_word(the_string):
	word = ''
	if ' ' in the_string:
		for index in range(len(the_string)):
			if the_string[index] != ' ':
				word += the_string[index]
			else:
				return word
	else:
		return the_string


def remove_word(the_string):
	for index in range(len(the_string)):
		if the_string[index] == ' ':
			return the_string[index + 1::]


def reverse_sentence(the_string):
	space_count = 0
	for index in range(len(the_string)):
		if the_string[index] == ' ':
			space_count += 1
	word_count = space_count + 1

	final_string = ''
	for x in range(1, word_count + 1):
		temp_string = the_string
		for y in range(0, word_count - x):
			temp_string = remove_word(temp_string)
		final_string += get_word(temp_string) + ' '
	return(final_string)


def main():
	user_input = input('Please enter a string to reverse: ')
	user_input_reverse = reverse_sentence(user_input)
	print('The reversed sentence is: \n %s' % user_input_reverse)

if __name__ == '__main__': main()
