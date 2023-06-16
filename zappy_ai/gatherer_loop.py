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
from commun import *
from datatypes import Creature, Session


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

def look_for(creature: Creature, last_actions: list, ia: Session, target: str):
    feild = look(ia.client)
    for item in feild:
        if item.__contains__(target):
            return item.index
    return -1

def spiral(i, ia: Session, last_action: list):
    while i > 0:
        i -= 1
        last_action.append(fowards(ia.client))
    last_action.append(right(ia.client))
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


def drop_all(creature: Creature, last_actions: list, ia: Session):
    inv = inventory(ia.client)
    while (inv.food <= 10) :
        last_actions.append(set_object(ia.client, "food"))
        inv.food -= 1
    creature.food = 10
    for item in inv :
        

def closest_resource(creature: Creature, last_actions: list, ia: Session):
    

def gatherer_loop(creature: Creature, last_actions: list, ia: Session) :
    resource_spotted = -1
    last_actions.append(fowards(ia.client))
    creature.var += 1
    if (creature.var % creature.map.size_x == 0) :
        last_actions.append(left(ia.client))
        last_actions.append(fowards(ia.client))
        last_actions.append(right(ia.client))
    resource_spotted = look_for(creature, last_actions, ia, "")
    if (resource_spotted != -1) :
        go_to(resource_spotted)
        last_actions.append(pick_up(ia.client))

    if something in view:
        while !something in view
            go_to
            pick_up
    if objective is met:
        return to base_pos
        drop everything
        pick up 20 20 food
    if called to base:
        go to base
        drop everytjing
    if enemy spotted:
        message enemy spotted
    if (food + 2) * 10 < distance to base():
        return to base()
        drop everything
        pick up 20 food