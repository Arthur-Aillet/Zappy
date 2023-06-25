## @package datatypes
# This module defines zappy classes

##
## EPITECH PROJECT, 2022
## zappy [WSL: Ubuntu]
## File description:
## datatypes.py
##

import server_action as sa
import server_get as sg
import communication as com
import uuid
from time import time


# class for a creature
class Creature:
    # Enum to define the differents roles an AI can take
    class Types: #enum
        max = 4 # update with the max value of the enum
        QUEEN = 0
        BABY = 1
        BUTLER = 2
        GATHERER = 3
        WARRIOR = 4

    def __init__(self):
        self.type = Creature.Types.BABY
        self.spawn_pos_x = 0
        self.spawn_pos_y = 0
        self.pos_x = 0
        self.pos_y = 0
        self.map = Map
        self.strvar = "Qu'est-ce que c'est? Hey, mais c'est les minables!"
        self.var = 0
        self.time_to_ritual = -1
        self.food = 0
        self.id = time()
        self.orientation = 0
        self.level = 1
        self.inventory = {'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
        self.last_look = [""]
        self.looked = False
        self.called = False
        self.confirmed = 0
        self.other_creatures_old = [{"lvl": 1, "role": Creature.Types.QUEEN, "id": 0, "messages": 0}]
        self.other_creatures = [{"lvl": 1, "role": Creature.Types.QUEEN, "id": 0, "messages": 0}]
        self.other_creatures_age = 0
        self.message_index = 0

# Holds the size of the map (x,y)
class Map:
    size_x = 10
    size_y = 10

# The Session class holds data about the current AI: it's socket client,
# type (role), relative position, direction, number of messages sents, id.
# It also holds aliases for client to server functions to use directly with the
# AI socket client.
class Session:
    def __init__(self, client, type=Creature.Types.BABY, pos=[0,0], direction=0):
        assert len(pos) == 2, "Session pos parameter should be of type [int,int]"
        assert isinstance(pos[0], int), "Session pos parameter should be of type [int,int]"
        assert isinstance(pos[1], int), "Session pos parameter should be of type [int,int]"
        assert type <= Creature.Types.max, "Type d'ia inconnu"
        assert direction <= 3 and direction >= 0, "Direciton invalide"

        self.client = client
        self.type = type
        self.pos = pos
        self.direction = direction
        self.msg_nb = 0
        self.id = uuid.uuid1() # s'assurer que c'est unique malgré les forks

    # server_action :

    def broadcast(self, text):
        output = sa.broadcast(self.client, text)
        self.msg_nb += 1
        return output
    def fowards(self):
        return sa.fowards(self.client)
    def left(self):
        return sa.left(self.client)
    def right(self):
        return sa.right(self.client)
    def pick_up(self):
        return sa.pick_up(self.client)
    def pick_up(self):
        return sa.fork(self.client)

    # server_get :

    def look(self):
        return sg.look(self.client)
    def inventory(self):
        return sg.inventory(self.client)

    # communication :

    def call_all(self):
        output = com.role_call(self.client, self.id, self.msg_nb)
        self.msg_nb += 1
        return output
    def say_type(self):
        output = com.say_type(self.client, self.id, self.nb)
        self.msg_nb += 1
        return output
