from math import *
from turtle import * 
from datetime import *

def kilo_pound():
	kilo = int(input('Please put in the weight in kilograms: '))
	KILO_POUND = 2.2046
	POUND_OUNCE = 16
	pounds_total = kilo * KILO_POUND
	pounds = str(pounds_total).split('.')[0]
	ounces_float = '.' + str(pounds_total).split('.')[1]
	ounces = float(ounces_float) * 16
	print('The answer is %s pounds and %s ounces' % (pounds, ounces))


def circular():
	radius = input('Please put in the radius of the circle: ')
	area = (int(radius) ** 2) * pi
	circumference = int(radius) * 2 * pi
	print('The area of the circle is %s and the circumeference is %s' % (area, circumference))


def draw_hexagon():
	setup(500,500)
	pendown()
	for x in range(0, 6):
		forward(50)
		right(60)
	penup()


def get_dob():
    dob = input('Please input your date of birth (YYYYMMDD): ')
    dob_year = int(dob[0:4:])
    dob_month = int(dob[4:6:])
    dob_day = int(dob[6::])

    dob_dateobject = date(dob_year, dob_month, dob_day)
    today_datetime = datetime.today()
    today_list = str(today_datetime).split(' ')[0].split('-')
    today_dateobject = date(int(today_list[0]), int(today_list[1]), int(today_list[2]))
    print('Today\'s date is %s' % today_dateobject)
    yes_no = input('Is that correct? (yes/no) \n')
    if yes_no == 'yes':
        days_difobject = str(today_dateobject - dob_dateobject)
        days_dif = int(days_difobject.split(' ')[0])

        years_between =  days_dif // 365
        months_between = (days_dif % 365) // 30
        days_between = (days_dif % 365) % 30

        print('You are %s years %s months and %s days old' % (years_between, months_between, days_between))
    else:
        get_dob()


def add_length():
    first_feet = input('Feet of the first length: ')
    first_inch = input('Inches of the first length: ')
    second_feet = input('Feet of the second length: ')
    second_inch = input('Inches of the second length: ')

    first_total = int(first_feet) * 12 + int(first_inch)
    second_total = int(second_feet) * 12 + int(second_inch)

    total = first_total + second_total

    print('The total is %s feet and %s inches' % (total//12,total%12))
