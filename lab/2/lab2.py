from math import *
from turtle import * 
from datetime import *

kilo = int(input('Please put in the weight in kilograms: '))
KILO_POUND = 2.2046
POUND_OUNCE = 16
pounds_total = kilo * KILO_POUND
pounds = str(pounds_total).split('.')[0]
ounces_float = '.' + str(pounds_total).split('.')[1]
ounces = float(ounces_float) * 16
print('The answer is %s pounds and %s ounces' % (pounds, ounces))


radius = input('Please put in the radius of the circle: ')
area = (int(radius) ** 2) * pi
circumference = int(radius) * 2 * pi
print('The area of the circle is %s and the circumeference is %s' % (area, circumference))


setup(500,500)
pendown()
for x in range(0, 6):
	forward(50)
	right(60)
penup()

