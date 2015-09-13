INITIAL_POPULATION = 307357870

print('The population now is %s' % INITIAL_POPULATION)
years = input('Please type the numbers of years: ')

year_days = int(years) * 365
year_hours = year_days * 24
year_minutes = year_hours * 60
year_seconds = year_minutes * 60

birth = round(year_seconds / 7)
death = round(year_seconds / 13)
immigration = round(year_seconds / 35)

new_population = INITIAL_POPULATION + birth - death + immigration

print('In %s years, the new population will be %s with %s births, %s deaths, and %s immigrants' % (years, new_population, birth, death, immigration))
