## @package server_action
# This module defines action functions for all the AI clients
#
# This module is "proprietary" to this type of AI, does not defines universal functions to
# send messages to a server but only defines actions that our zappy AI can make.

##
## EPITECH PROJECT, 2022
## zappy [WSL: Ubuntu]
## File description:
## server_action.py
##

from connect import send_server
from datatypes import ActionType
from os import fork

def broadcast(client, text):
    """!
    The function broadcasts a message to all AI clients connected to the server.

    @param client AI socket client
    @param text The message that will be broadcasted to all clients connected to the server.

    @return a boolean value (succes if sent, failure if so).
    """
    send_server(client, "Broadcast " + text)

def fowards(client):
    send_server(client, "Forward")
    return ActionType.OK_ACTION

def left(client):
    send_server(client, "Left")
    return ActionType.OK_ACTION

def right(client):
    send_server(client, "Right")
    return ActionType.OK_ACTION

def pick_up(client):
    send_server(client, "Take object")
    return ActionType.OK_ACTION

# si fork_ai return true la mainloop doit fork et l'enfant mainloop doit return True
def fork_ai(client):
    send_server(client, "Fork")
    return fork()
