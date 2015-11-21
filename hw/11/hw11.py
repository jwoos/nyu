'''

Name: Junwoo Shin
CS 1114
netID: js8460

The first function strips all other data out, leaving only city, date, high, low, and rainfall.
The second and third function converts the units the metric system (F -> C, in -> cm). The fourth function uses these to convert the whole file to metric.
The averages for each month are calculated and printed from the file.
In a similar fashion the average annual rainfall is calculated and printed.

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


# Part C
def print_averages_per_month(city, weather_filename, unit_type):
    f = open(weather_filename)
    
    city_data = []

    for row in f:
        row = row.split(',')
        if row[0] == city:
            city_data.append(row)
    # [high, low, count, high_average,low_average]
    averages = [None, [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]]

    for row in city_data:
        month = int(row[1].split('/')[0])
        averages[month][0] += float(row[2])
        averages[month][1] += float(row[3])
        averages[month][2] += 1

    for month in range(1, 12):
        averages[month].append(averages[month][0] / averages[month][2])
        averages[month].append(averages[month][1] / averages[month][2])

    print('Average temperatures for %s' % city)
    months = [None, 'January', 'Feburary', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']

    if unit_type == 'metric':
        for month in range(1, 12):
            print('%s: %1.2fC High, %1.2fC Low' % (months[month], averages[month][3], averages[month][4]))
    else:
        for month in range(1, 12):
            print('%s: %1.2fF High, %1.2fF Low' % (months[month], averages[month][3], averages[month][4]))


# Part D
# Q: Given two cities, which city has higher average precipitation?
def higher_rainfall(city1, city2, filename, unit_type):
    f = open(filename, 'r')
    
    city1_row = []
    city2_row = [] 
    
    for row in f:
        row = row.split(',')
        if row[0] == city1:
            city1_row.append(row)
        elif row[0] == city2:
            city2_row.append(row)
    
    # [total, count, average]
    city1_precip = [0, 0]
    city2_precip = [0, 0]

    for row in city1_row:
        city1_precip[0] += float(row[-1].strip())
        city1_precip[1] += 1

    for row in city2_row:
        city2_precip[0] += float(row[-1].strip())
        city2_precip[1] += 1

    city1_precip.append(city1_precip[0] / city1_precip[1])
    city2_precip.append(city2_precip[0] / city2_precip[1])
    
    if unit_type == 'metric':
        unit_type = 'cm'
    else:
        unit_type = 'in'

    if city1_precip[-1] > city2_precip[-1]:
        print('%s has a higher average rainfall with %1.2f%s' % (city1, city1_precip[-1], unit_type))
        print('%s had %1.2f%s' % (city2, city2_precip[-1], unit_type))
    else:
        print('%s has a higher average rainfall with %1.2f%s' % (city2, city2_precip[-1], unit_type))
        print('%s had %1.2f%s' % (city1, city1_precip[-1], unit_type))


def main():
    print ("Running Part A")
    clean_data("weather.csv", "weather in imperial.csv")
    
    print ("Running Part B")
    convert_data_to_metric("weather in imperial.csv", "weather in metric.csv")
    
    print ("Running Part C")
    print_averages_per_month("San Francisco", "weather in imperial.csv", "imperial")
    print_averages_per_month("New York", "weather in metric.csv", "metric")
    print_averages_per_month("San Jose", "weather in imperial.csv", "imperial")

    print ("Running Part D")
    # add your code here
    higher_rainfall('New York', 'San Francisco', 'weather in imperial.csv', 'imperial')     
    higher_rainfall('San Francisco', 'San Jose', 'weather in metric.csv', 'metric')     
    higher_rainfall('Los Angeles', 'New York', 'weather in imperial.csv', 'imperial')     
main()
