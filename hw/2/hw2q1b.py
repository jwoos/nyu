weight_pounds = int(input('Please input your weight in pounds: '))
height_inches = int(input('Please input your height in inches: '))

POUND_KILOGRAM = 0.453592
INCH_METER = 0.0254

weight_kilo = weight_pounds * POUND_KILOGRAM
height_meter = height_inches * INCH_METER

print('Your BMI is %s' % (weight_kilo/(height_meter**2)))
