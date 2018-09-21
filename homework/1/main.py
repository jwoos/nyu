#! /usr/bin/env python3

import socket


BUFFER_SIZE = 1024


def main(sock):
    while True:
        conn, addr = sock.accept()
        k


if __name__ == '__main__':
    try:
        sock = socket.socket(
            family=socket.AF_INET,
            type=socket.SOCK_STREAM,
        )
        sock.bind(('127.0.0.1', 8080))
        sock.listen()

        main(sock)
    finally:
        sock.close()
