##
## EPITECH PROJECT, 2023
## zappy
## File description:
## communication.py
##

# from connect import send_server
from server_action import broadcast

# client : server socket client
# id : ai id
# nb : number of messages already sent by this ai

def call_all(client, id, nb):
    return broadcast(client, str(id) + "-" + str(nb) + "-@everyone")

def say_type(client, id, nb):
    return broadcast(client, str(id) + "-" + str(nb) + "-@everyone")
