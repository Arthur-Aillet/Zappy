## @package connect
# This module enable to connect to a zappy server and send messages to it.
#
# This modules uses sockets to connect to a zappy server and send it messages.

##
## EPITECH PROJECT, 2023
## zappy
## File description:
## connect.py
##

import socket
from sys import stderr
from time import sleep

## Number of times to retry on connexion break
RETRY = 5

def connect(ip, port, team_name):
    """!
    The function connects to a zappy server using an IP address and port number, sends a team name,
    receives a response containing the number of places availables, the size x and y of the map,
    and returns these values.

    @param ip The IP address of the server to connect to.
    @param port The port parameter is the port number that the client socket will use to connect to the
    server socket.
    @param team_name The name of the team that is connecting to the server.

    @return The function `connect` returns a tuple containing a socket object (client),
    an integer representing the client number, and the size x and y of the map. If the
    client number is greater than or equal to 1, the client number, the places availables,
    and the size x y of the map are returned.
    Otherwise, everything is also returned but as the places availables is 0, the server refuses the
    connexion.
    """
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
    client.settimeout(0.07)
    if (client_num >= 1):
        return client, client_num, x, y
    return client, 0, x, y

def send_server(client, message):
    """!
    This function sends a message to a server and retries a RETRY number of times if it receives a
    'ko' response.

    @param client The client parameter is a socket object that represents a connection to a
    server. It is used to send a message to the server and receive a response.
    @param message The message parameter is a string that represents the message to be sent to the
    server. It is converted to bytes using the utf-8 encoding before being sent.

    @return the answer received from the server after sending a message to it. If the answer is 'ko\\n',
    the function will retry sending the message up to a maximum number of times specified by the RETRY
    constant. If the maximum number of retries is reached and the answer is still 'ko\\n', an error
    message will be printed to the standard error output.
    """
    print("sent to server :", message)
    client.send(bytes(message + "\n", "utf-8"))
