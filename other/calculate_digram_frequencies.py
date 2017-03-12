import sys
from decimal import Decimal, ROUND_HALF_EVEN

# This will be the length of the text passed into the program
NORMALIZE = 500

ROUND_DECIMAL = Decimal('.111111')

filename = sys.argv[1] or input('filename: ')

freq_number = {}
freq_percent = {}

print('Parsing %s' % filename)
f = open(filename)
text = f.read()
text_length = len(text)

for i in range(0, text_length - 1):
    digram = text[i] + text[i + 1]

    if freq_number.get(digram):
        freq_number[digram] += 1
    else:
        freq_number[digram] = 1

total = Decimal(text_length - 1)
for k in freq_number.keys():
    # freq_percent[k] = NORMALIZE * (Decimal(freq_number[k]) / total)
    freq_percent[k] = (Decimal(freq_number[k]) / total)
    freq_percent[k] = freq_percent[k].quantize(ROUND_DECIMAL, rounding=ROUND_HALF_EVEN)

data = ''
out_filename = filename[0:-4] + '_digram_frequency.txt'
file = open(out_filename, 'w')

test_sum = 0

TEXT = 'abcdefghijklmnopqrstuvwxyz '
for c in TEXT:
    temp = ''

    for h in TEXT:
        test_sum += freq_percent[c + h] if freq_percent.get(c + h) else 0

        temp += '%s, ' % freq_percent[c + h] if freq_percent.get(c + h) else '0, '

    data += '{' + temp + '}\n'

print('Total sum of frequencies: %s' % test_sum)

file.write(data)
print('Written to %s' % out_filename)
