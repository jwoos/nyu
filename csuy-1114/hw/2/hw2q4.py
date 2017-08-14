from datetime import *

john_days = input('Please enter the number of days John has worked: ')
john_hours = input('Please enter the number of hours John has worked: ')
john_minutes = input('Please enter the number of minutes John has worked: ')

bill_days = input('Please enter the number of days Bill has worked: ')
bill_hours = input('Please enter the number of hours Bill has worked: ')
bill_minutes = input('Please enter the number of minutes Bill has worked: ')

change1 = timedelta(days=int(bill_days),hours=int(bill_hours),minutes=int(bill_minutes))
change2 = timedelta(days=int(john_days),hours=int(john_hours),minutes=int(john_minutes))

total = change1 + change2
days = str(total).split(' ')[0]
hours = str(total).split(' ')[2].split(':')[0]
minutes = int(str(total).split(' ')[2].split(':')[1])

print('The total time they worked is: %s days, %s hours, and %s minutes' % (days, hours, minutes))
