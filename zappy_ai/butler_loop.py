#!/usr/bin/env python3
##
## EPITECH PROJECT, 2023
## zappy
## File description:
## warrior behaviour
##

from connect import connect
from server_get import *
from server_action import *
from sys import stderr
from datatypes import Creature, Session
from communication import *
from common import *

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
                return item.index
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
        if (creature.pos_y < creature.spawn_pos_y):
            while (creature.orientation != 0) :
                last_action.append(left(ia.client))
                creature.orientation -= 1
                creature.orientation %= 4
        elif (creature.pos_x < creature.spawn_pos_x):
            while (creature.orientation != 1) :
                last_action.append(left(ia.client))
                creature.orientation -= 1
                creature.orientation %= 4
        elif (creature.pos_y > creature.spawn_pos_y):
            while (creature.orientation != 2) :
                last_action.append(left(ia.client))
                creature.orientation -= 1
                creature.orientation %= 4
        elif (creature.pos_x > creature.spawn_pos_x):
            while (creature.orientation != 3) :
                last_action.append(left(ia.client))
                creature.orientation -= 1
                creature.orientation %= 4
        fowards(ia.client)
    creature.var = 0


def drop_all_food(creature: Creature, last_actions: list, ia: Session):
    invfood = creature.inventory.get('food')
    while (invfood >= 10) :
        last_actions.append(set_object(ia.client, "food"))
        invfood -= 1
    creature.food = 10

def butler_loop(creature: Creature, last_actions: list, ia: Session) :
    food_spotted = 0
    creature.var += 1
    spiral(creature.var, ia, last_actions, creature)
    if (distance_to_base(creature) > 90) :
        go_to_base(creature, ia, last_actions)
        drop_all_food(creature, last_actions, ia)
    food_spotted = look_for(creature, last_actions, ia, "food")
    if (food_spotted != -1) :
        go_to(food_spotted)
        last_actions.append(pick_up(ia.client, "food"))
    return False
    #ad queen order to return