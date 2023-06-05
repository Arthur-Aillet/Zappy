#!/usr/bin/env python3
##
## EPITECH PROJECT, 2023
## zappy
## File description:
## connect.py
##

import socket

def connect(ip, port, team_name):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, port))
    print("server message:", client.recv(1024))
    client.send(team_name + b'\n')

    client_num, x, y = client.recv(1024).replace(b'\n', b' ').split()
    print("server message 2:", client_num, x, y)
    client_num, x, y = int(client_num), int(x), int(y)
    print("clientnum x y", client_num, x, y)
    if (client_num >= 1):
        return client_num, x, y
    return client, 0, x, y
