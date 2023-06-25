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
    if creature.looked == False:
        creature.last_look = look(ia.client)
        creature.looked = True
    for item in creature.last_look:
        if item.__contains__(target):
            return item.index
    return -1

def closest_resource(creature: Creature, last_actions: list, ia: Session):
    if creature.looked == False:
        creature.last_look = look(ia.client)
        creature.looked = True
    for item in creature.last_look:
        if item != "" and item != "player":
            return item.index, item
    return -1

def spiral(i, ia: Session, last_action: list, creature: Creature):
    while i > 0:
        i -= 1
        last_action.append(fowards(ia.client))
        creature.pos_x, creature.pos_y = go_fowards(creature.pos_x, creature.pos_y, creature.orientation)
    last_action.append(right(ia.client))
    creature.orientation += 1
    creature.orientation %= 4
    return False

def distance_to_base(creature: Creature):
    return abs(creature.pos_x - creature.spawn_pos_x) + abs(creature.pos_y - creature.spawn_pos_y)

def go_to_base(creature: Creature, ia:Session, last_action: list):
    while (distance_to_base(creature) != 0):
        if (creature.pos_y < creature.spawn_pos_y and creature.pos_x != creature.spawn_pos_x):
            while (creature.orientation != 0) :
                last_action.append(left(ia.client))
                creature.orientation -= 1
                creature.orientation %= 4
        elif (creature.pos_x < creature.spawn_pos_x):
            while (creature.orientation != 1) :
                last_action.append(left(ia.client))
                creature.orientation -= 1
                creature.orientation %= 4
        elif (creature.pos_y > creature.spawn_pos_y and creature.pos_x != creature.spawn_pos_x):
            while (creature.orientation != 2) :
                last_action.append(left(ia.client))
                creature.orientation -= 1
                creature.orientation %= 4
        elif (creature.pos_x > creature.spawn_pos_x):
            while (creature.orientation != 3) :
                last_action.append(left(ia.client))
                creature.orientation -= 1
                creature.orientation %= 4
        last_action.append(fowards(ia.client))
        creature.pos_x, creature.pos_y = go_fowards(creature.pos_x, creature.pos_y, creature.orientation)
    creature.var = 0

def objectives(i: int):
    if (i == 0):
        return {'food': 0, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
    if (i == 1):
        return {'food': 0, 'linemate': 1, 'deraumere': 1, 'sibur': 1, 'mendiane': 0, 'phiras': 0, 'thystame': 0}
    if (i == 2):
        return {'food': 0, 'linemate': 2, 'deraumere': 0, 'sibur': 1, 'mendiane': 0, 'phiras': 2, 'thystame': 0}
    if (i == 3):
        return {'food': 0, 'linemate': 1, 'deraumere': 1, 'sibur': 2, 'mendiane': 0, 'phiras': 1, 'thystame': 0}
    if (i == 4):
        return {'food': 0, 'linemate': 1, 'deraumere': 2, 'sibur': 1, 'mendiane': 3, 'phiras': 0, 'thystame': 0}
    if (i == 5):
        return {'food': 0, 'linemate': 1, 'deraumere': 2, 'sibur': 3, 'mendiane': 0, 'phiras': 1, 'thystame': 0}
    if (i == 6):
        return {'food': 0, 'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 2, 'phiras': 2, 'thystame': 1}
    return {'food': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}

def pick_up_list(objective: dict[str, int], last_action: list, ai: Session):
    for key in objective :
        if key != "number":
            for _ in objective[key]:
                last_action.append(pick_up(ai.client, key))


