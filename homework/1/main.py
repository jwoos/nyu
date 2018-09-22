#! /usr/bin/env python3

import socket


BUFFER_SIZE = 1024


def main(sock):
    while True:
        conn, addr = sock.accept()
        message = []

        while True:
            received = conn.recv(BUFFER_SIZE)
            message.append(received)

            if len(received) < BUFFER_SIZE:
                break

        raw_message = b''.join(message)
        print(raw_message)
        # TODO parse http here

        conn.send(b'HTTP/1.1 200 OK\r\nServer: js8460\r\nContent-Length: 4\r\nContent-type: text/html\r\nConnection: Closed\r\n\r\ntest')


if __name__ == '__main__':
    try:
        sock = socket.socket(
            family=socket.AF_INET,
            type=socket.SOCK_STREAM,
        )
        # sock.bind(('127.0.0.1', 8080))
        sock.bind(('0.0.0.0', 8080))
        sock.listen()

        main(sock)
    finally:
        sock.close()
