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
from common import *
from communication import *
from datatypes import Creature, Session

def objective_met(i: int, inv: dict[str, int]):
    current = objectives(i)
    if inv.get("linemate") < current.get("linemate"):
        return False
    if inv.get("deraumere") < current.get("deraumere"):
        return False
    if inv.get("sibur") < current.get("sibur"):
        return False
    if inv.get("mendiane") < current.get("mendiane"):
        return False
    if inv.get("phiras") < current.get("phiras"):
        return False
    if inv.get("thystame") < current.get("thystame"):
        return False
    return True

def drop_all(creature: Creature, last_actions: list, ia: Session):
    invfood = creature.inventory.get("food")
    while (invfood >= 10) :
        last_actions.append(set_object(ia.client, "food"))
        invfood -= 1
    creature.food = 10
    for key in creature.inventory :
        if key != "food" :
            for _ in creature.inventory[key]:
                last_actions.append(set_object(ia.client, key))

def check_food(creature: Creature, last_actions: list, ia: Session):
    if (creature.inventory.get('food') < distance_to_base(creature) * 8) :
        creature.type = Creature.Types.BUTLER

def gatherer_loop(creature: Creature, last_actions: list, ia: Session) :
    resource_spotted = -1
    last_actions.append(fowards(ia.client))
    creature.pos_x, creature.pos_y = go_fowards(creature.pos_x, creature.pos_y, creature.orientation)
    creature.var += 1
    if (creature.var % creature.map.size_x == 0) :
        last_actions.append(left(ia.client))
        last_actions.append(fowards(ia.client))
        creature.pos_x, creature.pos_y = go_fowards(creature.pos_x, creature.pos_y, creature.orientation)
        last_actions.append(right(ia.client))
    resource_spotted, tile = closest_resource(creature, last_actions, ia, "")
    if (resource_spotted != -1) :
        go_to(resource_spotted)
        last_actions.append(pick_up(ia.client, tile.split(" ")[0]))

    if creature.var % 20 == 0 :
        if objective_met(creature.level, creature.inventory):
            go_to_base(creature, ia, last_actions)
            drop_all(creature, last_actions, ia)

    if creature.var % 20 == 10:
        check_food(creature, last_actions, ia)
    return False
