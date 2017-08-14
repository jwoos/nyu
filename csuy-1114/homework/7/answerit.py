import socket
import re

connection = socket.create_connection(('gnarlygno.me', 8888))

RETURN = '\r'

def convert_dec_bin(dec_num):
    return bin(dec_num)

def convert_dec_hex(dec_num):
    return hex(dec_num)

while connection:
    data_received = ''
    data_byte = connection.recv(4096)
    if not data_byte:
        break
    data_str = data_byte.decode('utf-8')
    print(data_str.strip())

    if re.match(r'(?:[a-zA-Z \d]+){0,1}\r\n\r\n', data_str):
        data_received = data_str.split('\r\n')[-2]
    else:
        data_received = data_str

    data_received = data_received.strip()
    matched_convert = re.match(r'Convert \((\d+)\) from base (\d+) to base \((\d+)\)', data_received)

    if matched_convert:
        number = int(matched_convert.group(1))
        base_from = int(matched_convert.group(2))
        base_to = int(matched_convert.group(3))
        data_to_send = ''

        if base_from == 10:
            if base_to == 2:
                data_to_send += convert_dec_bin(number)
            elif base_to == 16:
                data_to_send += convert_dec_hex(number)
            elif base_to == 10:
                data_to_send += str(number)
            print(data_to_send)
            data_to_send += RETURN
            data_to_send = data_to_send.encode()

        connection.sendall(data_to_send)

    matched_name = re.match(r'How to spell head TA name\?{3}', data_received)

    if matched_name:
        data_to_send = 'Salsaman'
        print(data_to_send)
        data_to_send = (data_to_send + RETURN).encode()
        connection.sendall(data_to_send)

# video = https://youtu.be/mAbTzPoJgWs
