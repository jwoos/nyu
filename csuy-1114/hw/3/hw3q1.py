weight = int(input('Please input your weight in kilograms: '))
height = float(input('Please input your height in meters: '))

bmi = weight / (height ** 2)

status = ''

if bmi < 18.5:
	status = 'underweight'
elif bmi < 24.9:
	status = 'normal'
elif bmi < 29.92:
	status = 'overweight'
else:
	status = 'obese'

print('Your BMI is %s and you are %s' % (bmi, status))
