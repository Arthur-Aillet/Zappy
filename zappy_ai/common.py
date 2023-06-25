#!/usr/bin/env python3
##
## EPITECH PROJECT, 2023
## zappy
## File description:
## common
##

from connect import connect
from server_get import *
from server_action import *
from sys import stderr
from datatypes import Session, Creature

def go_fowards(x, y, direction):
    if direction == 0:
        return x, y + 1
    if direction == 1:
        return x + 1, y
    if direction == 2:
        return x, y - 1
    if direction == 3:
        return x - 1, y

def go_to(i,creature: Creature, ia:Session, last_actions: list):
    row_max = 1
    while i < row_max :
        i -= row_max
        row_max += 2
    if (row_max / 2 < i):
        last_actions.append(left(ia.client))
        creature.orientation -= 1
        creature.orientation %= 4
    if (row_max / 2 > i):
        last_actions.append(right(ia.client))
        creature.orientation += 1
        creature.orientation %= 4
    for n in range(abs(row_max - (i))):
        last_actions.append(fowards(ia.client))
        creature.pos_x, creature.pos_y = go_fowards(creature.pos_x, creature.pos_y, creature.orientation)

def look_for(creature: Creature, last_actions: list, ia: Session, target: str):
    last_actions.append(look(ia.client))
    if creature.looked:
        for item in creature.last_look:
            if item.__contains__(target):
                return item.indexs
    return -1
