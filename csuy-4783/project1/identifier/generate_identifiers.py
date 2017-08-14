#!/usr/bin/env python3
import sys

UNIQUE_IDENTIFIERS = ['b', 'j', 'k', 'q', 'v', 'x', 'z']

filename = sys.argv[1] or input('filename: ')

f = open(filename)
text = f.read()

initial = {x: [] for x in UNIQUE_IDENTIFIERS}

for i in range(len(text)):
    if text[i] in UNIQUE_IDENTIFIERS:
        initial[text[i]].append(i)

print(initial)
