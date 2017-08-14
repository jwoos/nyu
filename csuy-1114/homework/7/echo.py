import socket as Socket

socket = Socket.socket(Socket.AF_INET, Socket.SOCK_STREAM)
socket.bind(('', 8080))
socket.listen(1)

conn, addr = socket.accept()

print('Connected by', addr)

while True:
    data = conn.recv(4096)
    if not data:
        break
    conn.sendall(data)

conn.close()
