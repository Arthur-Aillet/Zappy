##
## EPITECH PROJECT, 2023
## zappy
## File description:
## connect.py
##

import socket
from sys import stderr

RETRY = 5

def connect(ip, port, team_name):
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((ip, port))
    print("server message:", client.recv(1024))
    client.send(bytes(team_name, "utf-8") + b'\n')

    answer = client.recv(1024).replace(b'\n', b' ').split()
    if (len(answer) != 3):
        print("ko on connexion\n")
        exit(84)
    client_num, x, y = answer
    print("server message 2:", client_num, x, y)
    client_num, x, y = int(client_num), int(x), int(y)
    print("clientnum x y", client_num, x, y)
    if (client_num >= 1):
        return client, client_num, x, y
    return client, 0, x, y

def send_server(client, message):
    answer = b'ko\n'
    trys = 0
    while answer == b'ko\n' and trys < RETRY:
        trys += 1
        client.send(bytes(message + "\n", "utf-8"))
        answer = client.recv(1024)
    if answer == b'ko\n':
        stderr.write("ko on " + str(answer) + "\n")
    return answer
