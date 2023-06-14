## @package datatypes
# This module defines zappy classes

##
## EPITECH PROJECT, 2022
## zappy [WSL: Ubuntu]
## File description:
## datatypes.py
##

from connect import connect
from server_action import *
from server_get import *
from communication import *
import uuid

# Enum to define the differents roles an AI can take
class Types: #enum
    max = 1 # update with the max value of the enum
    BASIC = 0
    ATTACK = 1

# Holds the size of the map (x,y)
class Map:
    size_x = 10
    size_y = 10

# Enum to define the last action made
class ActionType: #enum
    max = 4
    NONE = 0
    OK_ACTION = 1 # simple action just asking for an ok
    LOOK = 2
    INVENTORY  = 3
    CALL_ALL = 4

# The Session class holds data about the current AI: it's socket client,
# type (role), relative position, direction, number of messages sents, id.
# It also holds aliases for client to server functions to use directly with the
# AI socket client.
class Session:
    def __init__(self, client, type=Types.BASIC, pos=[0,0], direction=0):
        assert len(pos) == 2, "Session pos parameter should be of type [int,int]"
        assert isinstance(pos[0], int), "Session pos parameter should be of type [int,int]"
        assert isinstance(pos[1], int), "Session pos parameter should be of type [int,int]"
        assert type <= Types.max, "Type d'ia inconnu"
        assert direction <= 3 and direction >= 0, "Direciton invalide"

        self.client = client
        self.type = type
        self.pos = pos
        self.direction = direction
        self.msg_nb = 0
        self.id = uuid.uuid1() # s'assurer que c'est unique malgré les forks

    # server_action :

    def broadcast(self, text):
        output = broadcast(self.client, text)
        self.msg_nb += 1
        return output
    def fowards(self):
        return fowards(self.client)
    def left(self):
        return left(self.client)
    def right(self):
        return right(self.client)
    def pick_up(self):
        return pick_up(self.client)

    # server_get :

    def look(self):
        return look(self.client)
    def inventory(self):
        return inventory(self.client)

    # communication :

    def call_all(self):
        output = call_all(self.client, self.id, self.msg_nb)
        self.msg_nb += 1
        return output
    def say_type(self):
        output = say_type(self.client, self.id, self.nb)
        self.msg_nb += 1
        return output
