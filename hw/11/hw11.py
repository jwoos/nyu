'''

Name: Junwoo Shin
CS 1114
netID: js8460

Purpose of program

'''


# Part A
def clean_data(complete_weather_filename, cleaned_weather_filename):
	f = open(complete_weather_filename, 'r')
	f_new = open(cleaned_weather_filename, 'a')

	header = f.readline().split(',')
	del header[4:8]
	del header[5:]
	f_new.write(','.join(header) + '\n')

	for row in f:
		row = row.split(',')
		del row[4:8]
		del row[5:]
		if row[-1] == 'T':
			row[-1] = '0'
		f_new.write(','.join(row) + '\n')

	f.close()
	f_new.close()

clean_data('weather.csv', 'weatherclean.csv')


# Part B
def f_to_c(f_temperature):
	c_temperature = (f_temperature - 32) / 1.8
	return c_temperature


def in_to_cm(inches):
	centimeters = inches / 0.39370
	return centimeters


def convert_data_to_metric(imperial_weather_filename, metric_weather_filename):
	f = open(imperial_weather_filename, 'r')
	f_new = open(metric_weather_filename, 'a')

	header = f.readline().split(',')
	f_new.write(','.join(header) + '\n')

	for row in f:
		row = row.split(',')
		row[2] = str(f_to_c(int(row[2])))
		row[3] = str(f_to_c(int(row[3])))
		row[4] = str(in_to_cm(float(row[4].strip())))
		f_new.write(','.join(row) + '\n')

	f.close()
	f_new.close()
convert_data_to_metric('weatherclean.csv', 'weathercleanmetric.csv')


# Part C
def print_averages_per_month(city, weather_filename, unit_type):
	pass


# Part D
# Write your question (as a comment), and implement a function to answer it


'''
def main():
    print ("Running Part A")
    clean_data("weather.csv", "weather in imperial.csv")
    
    print ("Running Part B")
    convert_data_to_metric("weather in imperial.csv", "weather in metric.csv")
    
    print ("Running Part C")
    print_average_temps_per_month("San Francisco", "weather in imperial.csv", "imperial")
    print_average_temps_per_month("New York", "weather in metric.csv", "metric")
    print_average_temps_per_month("San Jose", "weather in imperial.csv", "imperial")

    print ("Running Part D")
    # add your code here
    

    
main()
'''
