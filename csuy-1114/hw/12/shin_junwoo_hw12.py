'''

Name: Junwoo Shin
CS 1114
netID: js8460

First in the open_and read function I read the file and return it as an lust so that it's easier to work with.
I read the first line as that is not needed later on and then in a for loop I will read a line and then skip two; 
this is due to the file having station, stationN, stationS in order and would result in duplicates.

In the make_dict function, I make an empty dictionary to work with. Taking the list I made using open_and_list,
I go through each element (station). Since the first character of the stop_id is the train line, I'd use that as the key in the dict.
It checks if the key already exists and if it doesn't it'll add the station in a list! This is important so that later values can be added to it as well easily.
Later iterations will see that the key already exists and simply append the station to the list.

In the main method, I use the two functions to generate the dictionary that I'll be reading from. I make a while loop, simply using True as the conditional so I can break it later. 
Each iteration will ask for a line unless it's done.
I make a local variable called stations_to_print which is simply the value of the key (line) in the dict. This is an array as can be seen in the make_dict function.
I then print the first part of the output, using the user_input and use the optional argument end='' to prevent it going to a new line.
Then the function iterates using the index over the list that was obtained from the dictionary, printing each one with the argument of end=', '.
I used the index to iterate rather than the elements themselves so that I can get rid of the trailing comma by printing normally if it's the last element.

'''
def open_and_read(filename):
	f = open(filename)
	
	file_array = []
	first = f.readline()

	for line in f:
		line_list = line.split(',')
		file_array.append(line_list)
		f.readline()
		f.readline()
	
	return file_array

def make_dict(from_list):
	to_dict = {}
	for station in from_list:
		if station[0][0] in to_dict:
			to_dict[station[0][0]].append(station[2])
		else: 
			to_dict[station[0][0]] = [station[2]]
	return to_dict
	
def main():
	station_list = open_and_read('train-stop.csv')
	station_dict = make_dict(station_list)

	while True:
		user_input = input('Please enter a train line, or \'done\' to stop: ')

		if user_input == 'done':
			break

		stations_to_print = station_dict[user_input]
		
		print('%s line:' % user_input, end=' ')

		for station_i in range(len(stations_to_print)):
			if station_i != len(stations_to_print) - 1:
				print(stations_to_print[station_i], end=', ')
			else:
				print(stations_to_print[station_i])
main()
