digit_num = int(input('Please enter a number to transform into roman numerals: '))
thousands = digit_num // 1000
five_hundreds = (digit_num - (thousands * 1000)) // 500
hundreds = (digit_num - (thousands * 1000) - (five_hundreds * 500)) // 100
fifties = (digit_num - (thousands * 1000) - (five_hundreds * 500) - (hundreds * 100)) // 50
tens = (digit_num - (thousands * 1000) - (five_hundreds * 500) - (hundreds * 100) - (fifties * 50)) // 10
fives = (digit_num - (thousands * 1000) - (five_hundreds * 500) - (hundreds * 100) - (fifties * 50) - (tens * 10)) // 5
ones = (digit_num - (thousands * 1000) - (five_hundreds * 500) - (hundreds * 100) - (fifties * 50) - (tens * 10) - (fives * 5)) // 1
print('M' * thousands + 'D' * five_hundreds + 'C' * hundreds + 'L' * fifties + 'X' * tens + 'V' * fives + 'I' * ones)
