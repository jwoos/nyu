from decimal import Decimal

filename = input('filename: ')

freq_number = {}
freq_percent = {}

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
    freq_percent[k] = Decimal(freq_number[k]) / total

data = ''
file = open(filename[0:-4] + '_digram_frequency.csv', 'w')

TEXT = ' abcdefghijklmnopqrstuvwxyz'
for c in TEXT:
    for h in TEXT:
        data += '{"%s%s": %s}\n' % (c, h, freq_percent[c + h]) if freq_percent.get(c + h) else '{"%s%s": 0}\n' % (c, h)

file.write(data)
