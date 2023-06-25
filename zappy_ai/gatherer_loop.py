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
from communication import *
from datatypes import Creature, Session

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
    last_actions.append(look(ia.client))
    if creature.looked:
        for item in creature.last_look:
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
    invfood = creature.inventory.get("food")
    while (invfood >= 10) :
        last_actions.append(set_object(ia.client, "food"))
        invfood -= 1
    creature.food = 10
    for key in creature.inventory :
        if key != "food" :
            for _ in creature.inventory[key]:
                last_actions.append(set_object(ia.client, key))

def closest_resource(creature: Creature, last_actions: list, ia: Session):
    last_actions.append(look(ia.client))
    if creature.looked:
        for item in creature.last_look:
            if item == 'enemy':
                last_actions.append(broadcast(ia.client, "enemy_spotted" + creature.pos_x + " " + creature.pos_y))
            if item != "" and item != "player":
                return item.index, item
    return -1

def check_food(creature: Creature, last_actions: list, ia: Session):
    if (creature.inventory.get('food') < distance_to_base(creature) * 8) :
        creature.type = Creature.Types.BUTLER

def gatherer_loop(creature: Creature, last_actions: list, ia: Session) :
    resource_spotted = -1
    last_actions.append(fowards(ia.client))
    creature.var += 1
    if (creature.var % creature.map.size_x == 0) :
        last_actions.append(left(ia.client))
        last_actions.append(fowards(ia.client))
        last_actions.append(right(ia.client))
    resource_spotted, tile: str = closest_resource(creature, last_actions, ia, "")
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
