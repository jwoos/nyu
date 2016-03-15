import socket
import re

connection = socket.create_connection(('gnarlygno.me', 8888))

while connection:
    print('beginning')
    data_received = ''
    data_byte = connection.recv(4096)
    if not data_byte:
        break
    data_str = data_byte.decode('utf-8')
    print(data_str)

    if re.match(r'^\r\n\r\n', data_str):
        data_received = data_str.split('\r\n')[-2]
    else:
        data_received = data_str

    data_received = data_received.strip()
    matched = re.match(r'Convert \((\d+)\) from base (\d+) to base \((\d+)\)', data_received)

    if matched:
        print(matched.group(1))
        print(matched.group(2))
        print(matched.group(3))
        data_to_send = b'100'
        connection.sendall(data_to_send)
        print('sent')
    print('end')
