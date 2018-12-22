#! /usr/bin/env python3

import os
import sys


PADDING = '='
BYTE_GROUPING_LEGNTH = 3
BIT_GROUPING_LENGTH = 24
MAP_BIT_GROUPING_LENGTH = 6
MAX_LINE_LENGTH = 76

# RFC 2045 Table 1
MAPPING = (
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '+', '/',
)


# returns bits in MSB ordering
def bits(byte):
    return [
        ((byte[x]) >> i) & 1
        for x in range(len(byte))
        for i in reversed(range(8))
    ]


def main():
    if len(sys.argv) < 2:
        print('Pass a file to encode as base64')
        sys.exit(1)

    filename = sys.argv[1]
    if filename[0] != '/':
        filename = f'{os.getcwd()}/{filename}'

    with open(filename, 'rb') as f:
        data = f.read()
        encoded = []

        for i in range(0, len(data), BYTE_GROUPING_LEGNTH):
            bit_grouping = bits(data[i:i+BYTE_GROUPING_LEGNTH])
            bit_grouping_length = len(bit_grouping)
            padding = 0

            if bit_grouping_length < BIT_GROUPING_LENGTH:
                padding = (BIT_GROUPING_LENGTH - bit_grouping_length) // MAP_BIT_GROUPING_LENGTH
                diff = MAP_BIT_GROUPING_LENGTH - (bit_grouping_length % MAP_BIT_GROUPING_LENGTH)
                bit_grouping = bit_grouping + [0] * diff

            for j in range(0, len(bit_grouping), MAP_BIT_GROUPING_LENGTH):
                six_bit = bit_grouping[j:j+MAP_BIT_GROUPING_LENGTH]
                num = int(''.join((str(x) for x in six_bit)), 2)
                encoded.append(MAPPING[num])

            for _ in range(padding):
                encoded.append(PADDING)

        encoded_lines = []

        for i in range(0, len(encoded), MAX_LINE_LENGTH):
            encoded_lines.append(''.join(encoded[i:i+MAX_LINE_LENGTH]))

        with open(f'{filename}.BASE64', 'w+') as output:
            output.write('\n'.join(encoded_lines))

if __name__ == '__main__':
    main()
