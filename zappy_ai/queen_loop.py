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
from common import *

def ascending_objectives(i: int):
    if (i == 0):
        return {'number': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 1}
    if (i == 1):
        return {'number': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 1}
    if (i == 2):
        return {'number': 2, 'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 2}
    if (i == 3):
        return {'number': 2, 'linemate': 4, 'deraumere': 0, 'sibur': 3, 'mendiane': 0, 'phiras': 4, 'thystame': 0, "level": 3}
    if (i == 4):
        return {'number': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 1}
    if (i == 5):
        return {'number': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 1}
    if (i == 6):
        return {'number': 2, 'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 2}
    if (i == 7):
        return {'number': 2, 'linemate': 4, 'deraumere': 0, 'sibur': 3, 'mendiane': 0, 'phiras': 4, 'thystame': 0, "level": 3}
    if (i == 8):
        return {'number': 4, 'linemate': 4, 'deraumere': 4, 'sibur': 8, 'mendiane': 0, 'phiras': 4, 'thystame': 0, "level": 4}
    if (i == 9):
        return {'number': 4, 'linemate': 4, 'deraumere': 8, 'sibur': 4, 'mendiane': 12, 'phiras': 0, 'thystame': 0, "level": 5}
    if (i == 10):
        return {'number': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 1}
    if (i == 11):
        return {'number': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 1}
    if (i == 12):
        return {'number': 2, 'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 2}
    if (i == 13):
        return {'number': 2, 'linemate': 4, 'deraumere': 0, 'sibur': 3, 'mendiane': 0, 'phiras': 4, 'thystame': 0, "level": 3}
    if (i == 14):
        return {'number': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 1}
    if (i == 15):
        return {'number': 1, 'linemate': 1, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 1}
    if (i == 16):
        return {'number': 2, 'linemate': 2, 'deraumere': 2, 'sibur': 2, 'mendiane': 0, 'phiras': 0, 'thystame': 0, "level": 2}
    if (i == 17):
        return {'number': 2, 'linemate': 4, 'deraumere': 0, 'sibur': 3, 'mendiane': 0, 'phiras': 4, 'thystame': 0, "level": 3}
    if (i == 18):
        return {'number': 4, 'linemate': 4, 'deraumere': 4, 'sibur': 8, 'mendiane': 0, 'phiras': 4, 'thystame': 0, "level": 4}
    if (i == 19):
        return {'number': 4, 'linemate': 4, 'deraumere': 8, 'sibur': 4, 'mendiane': 12, 'phiras': 0, 'thystame': 0, "level": 5}
    if (i == 20):
        return {'number': 6, 'linemate': 6, 'deraumere': 12, 'sibur': 18, 'mendiane': 0, 'phiras': 6, 'thystame': 0, "level": 7}
    if (i == 21):
        return {'number': 6, 'linemate': 12, 'deraumere': 12, 'sibur': 12, 'mendiane': 12, 'phiras': 12, 'thystame': 6, "level": 5}
    return {'number': 0, 'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0}

def parrot(ai: Session, creature: Creature, last_action: list):
    last_action.append(broadcast(ai.client, creature.strvar))
    creature.message_index += 1

def stockpile_contains(objective: dict[str, int], tile: str):
    if objective.get("linemate") < tile.count("linemate"):
        return False
    if objective.get("deraumere") < tile.count("deraumere"):
        return False
    if objective.get("sibur") < tile.count("sibur"):
        return False
    if objective.get("mendiane") < tile.count("mendiane"):
        return False
    if objective.get("phiras") < tile.count("phiras"):
        return False
    if objective.get("thystame") < tile.count("thystame"):
        return False
    return True

def call_all_roles(creature: Creature, ai: Session):
    creature.other_creatures_old = creature.other_creatures.copy()
    creature.other_creatures = [{"lvl": 1, "role": Creature.Types.QUEEN, "id": 0, "messages": 0}]
    creature.other_creatures_age = 0
    ai.call_all()

def take_new_role_in_account(msg_info: str, creature: Creature):
    temp_info = msg_info.text.split()
    for i in creature.other_creatures:
        if i["id"] == msg_info.id:
            return
    if msg_info.text.startswith("my job is "):
        creature.other_creatures.append({
            "lvl": temp_info[4],
            "role": temp_info[3],
            "id": msg_info.id,
            "messages": msg_info.number
        })

def select_n_people_of_level(creature: Creature, n: int, lvl: int):
    result: list[dict[str, int]] = []
    selected = 0
    for crt in creature.other_creatures:
        if crt.get("lvl") == lvl and selected < n and crt.get("role") != Creature.Types.QUEEN:
            result.append(crt)
            selected += 1
    if selected < n:
        return []
    else:
        return result

def role_weighting(creatures: list[dict[str, int]], last_action: list, ai: Session, ordering_creature: Creature):
    queen = 0
    butler = 0
    warrior = 0
    gatherer = 0
    total = 0
    for creature in creatures:
        if creature.get("role") == Creature.Types.QUEEN:
            queen += 1
        if creature.get("role") == Creature.Types.BUTLER:
            butler += 1
        if creature.get("role") == Creature.Types.WARRIOR:
            warrior += 1
        if creature.get("role") == Creature.Types.GATHERER:
            gatherer += 1
    if len(creatures) > 5 :
        while queen > 1:
            selected: dict[str, int]
            for creature in creatures:
                if creature.get("role") == Creature.Types.QUEEN:
                    selected = creature
            change_profession(ai.client, ordering_creature.id, ordering_creature.message_index, creature.get("id"), Creature.Types.GATHERER)
            ordering_creature.message_index += 1
            queen -= 1
        while butler > 1:
            selected: dict[str, int]
            for creature in creatures:
                if creature.get("role") == Creature.Types.BUTLER:
                    selected = creature
            change_profession(ai.client, ordering_creature.id, ordering_creature.message_index, creature.get("id"), Creature.Types.GATHERER)
            ordering_creature.message_index += 1
            butler -= 1
        while butler < 1:
            selected: dict[str, int]
            for creature in creatures:
                if creature.get("role") != Creature.Types.BUTLER and creature.get("role") != Creature.Types.QUEEN:
                    selected = creature
            change_profession(ai.client, ordering_creature.id, ordering_creature.message_index, creature.get("id"), Creature.Types.BUTLER)
            ordering_creature.message_index += 1
            butler += 1
        while warrior / warrior + gatherer > 0.3:
            selected: dict[str, int]
            for creature in creatures:
                if creature.get("role") == Creature.Types.WARRIOR:
                    selected = creature
            change_profession(ai.client, ordering_creature.id, ordering_creature.message_index, creature.get("id"), Creature.Types.GATHERER)
            ordering_creature.message_index += 1
            warrior -= 1
        while warrior / warrior + gatherer < 0.2:
            selected: dict[str, int]
            for creature in creatures:
                if creature.get("role") == Creature.Types.GATHERER:
                    selected = creature
            change_profession(ai.client, ordering_creature.id, ordering_creature.message_index, creature.get("id"), Creature.Types.WARRIOR)
            ordering_creature.message_index += 1
            warrior += 1

def queen_loop(creature: Creature, last_Action: list, ia: Session, message: messageinfo):
    creature.var += 1
    creature.var %= 20;
    creature.other_creatures_age += 1

    # if (id != 0) :
    #     creature.type = Creature.Types.BUTLER

    if creature.food < 10:
        if (look_for(creature, last_Action, ia, "food") == 0):
            last_Action.append(pick_up(ia.client, "food"))
        else:
            parrot(ia, creature, last_Action)
    if distance_to_base(creature) > 0:
        go_to_base(creature, ia, last_Action)
    if (creature.var == 0) :
        if fork_ai(ia.client) == 0:
            return True
        last_Action.append(ActionType.FORK)
    if creature.looked:
        if (stockpile_contains(ascending_objectives(creature.level), creature.last_look[0])):
            if creature.called == False:
                creature.confirmed = 0
                selected = select_n_people_of_level(creature,ascending_objectives(creature.level).get("number"), ascending_objectives(creature.level).get("level") )
                for crt in selected:
                    move_to_base(ia.client, creature.id, creature.message_index, crt.get("id"))
                    creature.message_index += 1
                creature.called = True
    if messageinfo.valid and messageinfo.text.startswith("bien arrive"):
        creature.confirmed += 1
    if creature.called == True and creature.confirmed == ascending_objectives(creature.level).get("number"):
        last_Action.append(ritual_in(ia.client, creature.id, creature.message_index, 11))
        creature.message_index += 1
    if message.valid and message.text.startswith("here's info"):
        orientation = creature.orientation
        if message.direction == 3:
            orientation -= 1
        if message.direction == 5:
            orientation -= 2
        if message.direction == 7:
            orientation -= 3
        orientation %= 4
        give_info(ia.client, creature.id, creature.message_index, message.id, creature, orientation, Creature.Types.BUTLER)
        creature.message_index += 1
    if creature.var == 10:
        last_Action.append(role_call(ia.client, creature.id, creature.message_index))
        creature.message_index += 1
        role_weighting(creature.other_creatures, last_Action, ia, creature)
    if message.valid == False and message.text != "":
        creature.strvar = message.text
    return False