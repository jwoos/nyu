from datetime import *

dob = input('Please input your date of birth (YYYYMMDD): ')
dob_year = int(dob[0:4:])
dob_month = int(dob[4:6:])
dob_day = int(dob[6::])

dob_dateobject = date(dob_year, dob_month, dob_day)
today_datetime = datetime.today()
today_list = str(today_datetime).split(' ')[0].split('-')
today_dateobject = date(int(today_list[0]), int(today_list[1]), int(today_list[2]))

days_difobject = str(today_dateobject - dob_dateobject)
days_dif = int(days_difobject.split(' ')[0])


days_left = days_dif % 365
years_between = (days_dif - days_left) / 365
months_between = days_left % 30

print('You are %s years old', % (years_between))
