#! /usr/bin/env python3

import socket


HTTP_VERSION = 1.1
BUFFER_SIZE = 128
STATUS_MESSAGES = {
    200: 'OK',
    404: 'Not Found',
    405: 'Method Not Allowed',
}


class Request:
    def __init__(self, conn):
        self.conn = conn
        self.http_version = None
        self.method = None
        self.path = None
        self.header = {}
        self.message = None
        self.body = None

        self.message_list = []
        self.body_list = []

        while True:
            received = conn.recv(BUFFER_SIZE)
            self.message_list.append(received)

            if len(received) < BUFFER_SIZE:
                break

        self.message = b''.join(self.message_list).decode()

        lines = self.message.split('\r\n')

        request_line = lines[0].split(' ')
        self.method = request_line[0]
        self.path = request_line[1]
        self.http_version = request_line[2]

        for line in lines[1:]:
            if line:
                header = line.split(': ')
                self.header[header[0]] = ': '.join(header[1:])

            else:
                break

        if self.header.get('Content-Length', None):
            length = int(self.header['Content-Length'])

            while True:
                to_receive = min(length, BUFFER_SIZE)
                self.body_list.append(conn.recv(to_receive))
                length -= to_receive
                if length <= 0:
                    break

            self.body = b''.join(self.body_list).decode()


class Response:
    def __init__(
        self,
        conn,
        http_version='HTTP/1.1',
        code=200,
        header={},
        body=''
    ):
        self.conn = conn
        self.http_version = http_version
        self.code = code
        self.header = header
        self.body = body


    def form(self):
        response = [
            f'{self.http_version} {self.code} {STATUS_MESSAGES[self.code]}\r\n',
        ]

        self.header['Content-Length'] = len(self.body)
        for k, v in self.header.items():
            response.append(f'{k}: {v}\r\n')

        response.append('\r\n')
        response.append(body)

        return ''.join(response).encode()


def main(sock):
    while True:
        conn, addr = sock.accept()

        req = Request(conn)

        # resp = Response(conn)

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
