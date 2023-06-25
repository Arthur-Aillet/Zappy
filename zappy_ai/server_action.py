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

from sys import exit
import unexpected
from connect import send_server
from action_type import ActionType
from os import fork
import socket

def reception(client):
    print("in reception")
    message = ""
    try:
        message = client.recv(1024).decode()
        print("got server message :", message)
    except socket.timeout:
        # err = e.args[0]
        # this next if/else is a bit redundant, but illustrates how the
        # timeout exception is setup
        message = ""
    except socket.error:
        # Something else happened, handle error, exit, etc.
        print("socket error")
        exit(0)
    else:
        if len(message) == 0:
            print ('server shutdown')
            exit(0)
    while message == "" or message.startswith("Message") or message.startswith("dead"):
        if message != "":
            unexpected.unexpected_msg.append(message)
        try:
            message = client.recv(1024).decode()
            print("got server message :", message)
        except socket.timeout:
            # err = e.args[0]
            # this next if/else is a bit redundant, but illustrates how the
            # timeout exception is setup
            message = ""
            continue
        except socket.error:
            # Something else happened, handle error, exit, etc.
            print("socket error")
            exit(0)
        else:
            if len(message) == 0:
                print ('server shutdown')
                exit(0)
    print("out reception")
    return message

def broadcast(client, text):
    """!
    The function broadcasts a message to all AI clients connected to the server.

    @param client AI socket client
    @param text The message that will be broadcasted to all clients connected to the server.

    @return a boolean value (succes if sent, failure if so).
    """
    send_server(client, "Broadcast " + text)
    reception(client)

    return ActionType.OK_ACTION


def fowards(client):
    """!
    Send the forward command to the server.

    @param client Ai socket client
    """
    send_server(client, "Forward")
    reception(client)
    return ActionType.OK_ACTION

def left(client):
    """!
    Send the left command to the server.

    @param client Ai socket client
    """
    send_server(client, "Left")
    reception(client)
    return ActionType.OK_ACTION

def right(client):
    """!
    Send the right command to the server.

    @param client Ai socket client
    """
    send_server(client, "Right")
    reception(client)
    return ActionType.OK_ACTION

def pick_up(client, object: str):
    """!
    Send the pick up command to the server.

    @param client Ai socket client and object
    """
    send_server(client, "Take " + object)
    reception(client)
    return ActionType.OK_ACTION

def set_object(client, object: str):
    """!
    Send the set object command to the server.

    @param client Ai socket client and object
    """
    send_server(client, "Set " + object)
    reception(client)
    return ActionType.OK_ACTION

# si fork_ai return true la mainloop doit fork et l'enfant mainloop doit return True
def fork_ai(client):
    """!
    Send the fork command to the server.

    @param client Ai socket client
    @return Returns the PID given by the fork() function. (0 = child)
    """
    send_server(client, "Fork")
    reception(client)
    return fork()

