prices = [0, 0]
prices[0] = int(input('Please input an item\'s price: '))
prices[1] = int(input('Please input another item\'s price: '))

member = input('Do you have a membership? (y/n): ').lower()
tax_rate = float(input('What\'s the tax rate?: ')) / 100

base_price = prices[0] + prices[1]

discounted = 0

if member == 'y':
	discounted = (max(prices) + (min(prices) / 2)) * 0.9
else:
	discounted = max(prices) + (min(prices) / 2)

total = round(discounted + (discounted * tax_rate), 2)

print('The base price is', base_price)
print('The discounted price is', discounted)
print('The total is', total)
