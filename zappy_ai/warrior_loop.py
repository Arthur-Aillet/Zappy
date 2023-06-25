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
                return item.indexs
    return -1

def check_food(creature: Creature, last_actions: list, ia: Session):
    if (creature.inventory.get('food') < 10) :
        creature.type = Creature.Types.GATHERER

def warrior_loop(creature: Creature, last_actions: list, ia: Session, message: messageinfo):
    #add answer to messages
    if (creature.var % 10 == 0) :
        check_food()
    last_actions.append(fowards(ia.client))
    enemypos = look_for(creature, last_actions, ia, "enemy")
    if (enemypos != -1):
        enemy_spotted(ia.client, creature.id, creature.message_index, creature.pos_x)
        creature.confirmed = 3
    if creature.confirmed == 0:
        go_to(enemypos)
        send_server(ia.client, "Eject\n")
        creature.confirmed = -1
    if creature.confirmed >= 0:
        creature.confirmed -= 1
        if messageinfo.valid and messageinfo.text.startswith("don't shoot"):
            creature.confirmed = -1
    last_actions.append(fowards(ia.client))
    return False
