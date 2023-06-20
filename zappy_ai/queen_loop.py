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


def parrot(ia: Session, creature: Creature, last_action: list):
    last_action.append(broadcast(creature.strvar))

def look_for(creature: Creature, last_actions: list, ia: Session, target: str):
    last_actions.append(look(ia.client))
    if creature.looked:
        for item in creature.last_look:
            if item.__contains__(target):
                return item.indexs
    return -1

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

def distance_to_base(creature: Creature):
    return abs(creature.pos_x - creature.spawn_pos_x) + abs(creature.pos_y - creature.spawn_pos_y)

def queen_loop(creature: Creature, last_Action: list, ia: Session):
    creature.var += 1
    creature.var %= 20;

    if (id != 0) :
        creature.type = Creature.Types.BUTLER

    if creature.food < 10:
        if (look_for(creature, last_Action, ia, "food") == 0):
            last_Action.append(pick_up())
        else:
            parrot(ia, creature, last_Action)
    if distance_to_base > 0:
        go_to_base(creature, ia, last_Action)
    if (creature.var == 0) :
        return True
    if i == 5:
        if (rocks on the floor are sufficient for next step (objective))
            if called == false
                call the closest level apropriate people to base_pos. priority on butler then gatherers then warriors then babys then queen
                objective += 1
            else
                if people on same tile == number required + 1
                    ritual order
    if creature.var == 10
        job status;
        get responses;
        if (percentages are not good)
            take random people from too numerous groups and change their profession
    if (someone need info)
        say infos
    else ():
        parrot();
    return False