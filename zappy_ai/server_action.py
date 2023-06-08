##
## EPITECH PROJECT, 2022
## zappy [WSL: Ubuntu]
## File description:
## server_action.py
##

from connect import send_server

def broadcast(client, text):
    if send_server(client, "Broadcast " + text) == b'ok\n':
        return True
    return False

def fowards(client):
    if send_server(client, "Forward") == b'ok\n':
        return True
    return False

def left(client):
    if send_server(client, "Left") == b'ok\n':
        return True
    return False

def right(client):
    if send_server(client, "Right") == b'ok\n':
        return True
    return False

def pick_up(client):
    if send_server(client, "Take object") == b'ok\n':
        return True
    return False

# si fork_ai return true la mainloop doit fork et l'enfant mainloop doit return True
def fork_ai(client):
    if send_server(client, "Fork") == b'ok\n':
        return True
    return False
