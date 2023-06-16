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

def parrot(ia: Session, creature: Creature):
    ia.broadcast(creature.strvar)

def nearest_food(ia: Session):
    items = look(ia.client)
    for item in items :
        if item.__contains__("food"):
            return item.index

def queen_loop(creature: Creature, last_message, ia: Session):
    creature.var += 1
    creature.var %= 20;

    if (id != 0) :
        creature.type = Creature.Types.BUTLER

    if creature.food < 10:
        if (nearest_food == 0):
            ia.pick_up()
        else:
            ia.broadcast()
    if pos != base_pos:
        move_to(base_pos.x, base_pos.y)
    if (i == 0) :
        fork;
        job status;
        get responses;
        if (percentages are not good)
            take random people from too numerous groups and change their profession
    if i == 5:
        if (rocks on the floor are sufficient for next step (objective[0]))
            if called == false
                call the closest level apropriate people to base_pos. priority on butler then gatherers then warriors then babys then queen
                objective += 1
            else
                if people on same tile == number required + 1
                    ritual order
    if (someone need info)
        say infos
    else ():
        parrot();