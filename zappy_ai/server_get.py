## @package server_get
# This module defines get functions for all the AI clients to get data
#
# This module is "proprietary" to this type of AI, does not defines universal functions to
# send messages to a server but only defines actions that our zappy AI can make.

##
## EPITECH PROJECT, 2022
## zappy [WSL: Ubuntu]
## File description:
## server_get.py
##

from connect import send_server

def look(client):
    """!
    Zappy Look function

    The AI will look in front of itself.

    @param client Socket client

    @return Return an array representing the field of view of the AI conformed to the
    Zappy documentation.
    """
    answer = str(send_server(client, "Look"))[4:-6].split(", ")
    for i in range(len(answer)):
        answer[i] = answer[i].split()
    return answer

def inventory(client):
    """!
    Zappy inventory function

    Gives the actual inventory of the AI

    @param client Socket client

    @return Return a dict representing the inventory of the AI for each type of ressource,
    conformed to the Zappy documentation.
    """
    answer = send_server(client, "Inventory")
    if len(answer) < 5:
        return {'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
    answer = str(answer)[4:-5].replace(',', '').split()
    if len(answer) % 2 != 0:
        return {'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
    output = {}
    for i in range(0, len(answer), 2):
        output[answer[i]] = int(answer[i + 1])
    return output