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
    client.send(team_name + '\n')

    client_num = client.recv(1024)
    x, y = client.recv(1024).strip()
    x, y = int(x), int(y)
    if (client_num >= 1):
        return client_num, x, y
    return 0, x, y
