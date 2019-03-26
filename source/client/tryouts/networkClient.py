#!/usr/bin/env python3

import socket

HOST = 'upboard'  # The server's hostname or IP address
PORT = 65432        # The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b'Hello, world1')
    print('sent: Hello, world1')

    s.sendall(b'Hello, world2')
    print('sent: Hello, world2')

    data = s.recv(1024)

print('Received', repr(data))