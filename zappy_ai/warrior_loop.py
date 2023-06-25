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

def check_food(creature: Creature, last_actions: list, ia: Session):
    if (creature.inventory.get('food') < 10) :
        creature.type = Creature.Types.GATHERER

def warrior_loop(creature: Creature, last_actions: list, ia: Session, message: messageinfo):
    #add answer to messages
    if (creature.var % 10 == 0) :
        check_food()
    last_actions.append(fowards(ia.client))
    creature.pos_x, creature.pos_y = go_fowards(creature.pos_x, creature.pos_y, creature.orientation)
    enemypos = look_for(creature, last_actions, ia, "enemy")
    if (enemypos != -1):
        enemy_spotted(ia.client, creature.id, creature.message_index, creature.pos_x)
        creature.message_index += 1
        creature.confirmed = 3
    if creature.confirmed == 0:
        go_to(enemypos)
        send_server(ia.client, "Eject\n")
        creature.confirmed = -1
    if creature.confirmed >= 0:
        creature.confirmed -= 1
        if messageinfo.valid and messageinfo.text.startswith("don't shoot"):
            creature.confirmed = -1
    return False
