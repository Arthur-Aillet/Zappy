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

def parrot(ai: Session, creature: Creature, last_action: list):
    last_action.append(broadcast(ai.client, creature.strvar))

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

def pick_up_list(objective: dict[str, int], last_action: list, ai: Session):
    for key in objective :
        if key != "number" :
            for _ in objective[key]:
                last_action.append(pick_up(ai.client, key))

def distance_to_base(creature: Creature):
    return abs(creature.pos_x - creature.spawn_pos_x) + abs(creature.pos_y - creature.spawn_pos_y)

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

def queen_loop(creature: Creature, last_Action: list, ia: Session):
    creature.var += 1
    creature.var %= 20;
    creature.other_creatures_age += 1

    if (id != 0) :
        creature.type = Creature.Types.BUTLER

    if creature.food < 10:
        if (look_for(creature, last_Action, ia, "food") == 0):
            last_Action.append(pick_up(ia.client, "food"))
        else:
            parrot(ia, creature, last_Action)
    if distance_to_base(creature) > 0:
        go_to_base(creature, ia, last_Action)
    if (creature.var == 0) :
        return True
    if creature.looked:
        if (stockpile_contains(ascending_objectives(creature.level), creature.last_look[0])):
            if creature.called == False:
                # call the closest level apropriate people to base_pos. priority on butler then gatherers then warriors then babys then queen
                creature.called = True
    if creature.called == True and creature.confirmed == ascending_objectives(creature.level).get("number"):
        pick_up_list()
        last_Action.append(ritual_in(ia.client, creature.id, creature.message_index))
        creature.message_index += 1
    if creature.var == 10:
        last_Action.append(role_call(ia.client, creature.id, creature.message_index))
        creature.message_index += 1
        # get responses;
        # if (percentages are not good)
        #     take random people from too numerous groups and change their profession
    # if (someone need info)
    #     say infos
    else:
        parrot(ia, creature, last_Action);
    return False