# 2
def convert_dec_bin(dec_num):
    bin_num = bin(dec_num)
    print(bin_num)
    return bin_num

dec_bin_list = [57, 123, 85, 38]

for dec_num in dec_bin_list:
    convert_dec_bin(dec_num)

# 3
def convert_hex_ascii(hex_num_list):
    output = ''
    for hex_num in hex_num_list:
        output += chr(hex_num)
    print(output)
    return output

hex_ascii_list =  [
    [0x41, 0x53, 0x43, 0x49, 0x49, 0x20, 0x77, 0x68, 0x61, 0x74, 0x20, 0x79, 0x6f, 0x75, 0x20, 0x64, 0x69, 0x64, 0x20, 0x74, 0x68, 0x65, 0x72, 0x65],
    [0x39, 0x41, 0x4d, 0x20, 0x69, 0x73, 0x20, 0x74, 0x6f, 0x6f, 0x20, 0x65, 0x61, 0x72, 0x6c,
0x79, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x63, 0x6c, 0x61, 0x73, 0x73],
    [0x43, 0x6f, 0x6d, 0x70, 0x75, 0x74, 0x65, 0x72, 0x73, 0x20, 0x61, 0x72, 0x65, 0x20,
0x6d, 0x61, 0x67, 0x69, 0x63],
    [0x57, 0x68, 0x61, 0x74, 0x20, 0x74, 0x68, 0x65, 0x20, 0x68, 0x65, 0x78, 0x3f]
]

for hex_num_list in hex_ascii_list:
    convert_hex_ascii(hex_num_list)

# 4
def convert_bin_hex(bin_num):
    dec_num = int(bin_num)
    hex_num = hex(dec_num)
    print(hex_num)
    return hex_num

bin_hex_list = [0b00001011101011101101111010101101, 0b11001010111111101111101011001110, 0b10111110111011111101000000001101, 0b11111111111111111001000001100010]

for bin_num in bin_hex_list:
    convert_bin_hex(bin_num)

# 5
def convert_oct_dec(oct_num):
    oct_num = str(oct_num)
    oct_num_list = list(oct_num)
    oct_num_list.reverse()
    oct_num_enum = enumerate(oct_num_list)
    dec_num = 0
    for digit in oct_num_enum:
        dec_num += int(digit[1]) * (8 ** digit[0])
    print(dec_num)
    return dec_num

oct_dec_list = [10, 42, 77, 113]

for oct_num in oct_dec_list:
    convert_oct_dec(oct_num)
