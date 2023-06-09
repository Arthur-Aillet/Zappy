#!/usr/bin/env python3
##
## EPITECH PROJECT, 2022
## zappy [WSL: Ubuntu]
## File description:
## datatypes.py
##

from connect import connect
from server_action import *
from server_get import *
import uuid

class Types: #enum
    max = 1 # update with the max value of the enum
    BASIC = 0
    ATTACK = 1

class Map:
    size_x = 10
    size_y = 10

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

    def broadcast(self, text):
        return broadcast(self.client, text)
    def fowards(self):
        return fowards(self.client)
    def left(self):
        return left(self.client)
    def right(self):
        return right(self.client)
    def pick_up(self):
        return pick_up(self.client)

    def look(self):
        return look(self.client)
    def inventory(self):
        return inventory(self.client)
