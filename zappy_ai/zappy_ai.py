#!/usr/bin/env python3
##
## EPITECH PROJECT, 2023
## zappy
## File description:
## zappy_ai
##

from connect import connect
from communication import getmsginfo
from server_get import *
from server_action import *
from sys import stderr
from datatypes import Session, ActionType, Creature
from gatherer_loop import gatherer_loop
from queen_loop import queen_loop, take_new_role_in_account
from warrior_loop import warrior_loop
from butler_loop import butler_loop

def look_arround():
    found_obj = -1
    for i in range(4):
        found_obj = look
        if (found_obj != -1):
            return found_obj
    return found_obj


def loop(switch, spiral_len):
    switch += 1
    if switch % 2 == 0:
        spiral_len += 1
    if spiral(spiral_len):
        go_to(look)
        pick_up()
        while look_arround != -1:
            go_to(look_arround)
            pick_up()

def mainloop(ai: Session): # mainloop peut return True si elle est enfant de fork / false si stop
    looping = True
    last_actions = []
    creature = Creature()

    while looping:
        message = ai.client.recv().decode() # peut être mettre un timeout pour éviter de rester perdu sur une interrupt de co

        # gestion des envois inopinés du serveur
        if message.startswith("Message "):
            creature.strvar = message
            msg_info = getmsginfo(message, creature)
            if msg_info.text.startswith("my job is "):
                take_new_role_in_account(msg_info, creature)
            continue # traiter le maissage

        # gestion des envois prévus du serveur (si une récéption est prévue)
        if (len(last_actions) == 0):
            continue
        if (last_actions[0] == ActionType.NONE):
            last_actions.pop(0)
            continue

        if creature.time_to_ritual == 0:
            send_server(ai.client, "Incantation\n")
            creature.level += 1
        if creature.time_to_ritual >= 0 :
            creature.time_to_ritual -= 1;
        if (creature.type == Creature.Types.QUEEN) :
            queen_loop(creature, last_actions)
        if (creature.type == Creature.Types.BUTLER) :
            butler_loop(creature, last_actions)
        if (creature.type == Creature.Types.GATHERER) :
            gatherer_loop(creature, last_actions)
        if (creature.type == Creature.Types.WARRIOR) :
            warrior_loop(creature, last_actions)
        # traitement de tous les cas de reception en fonction de last_action[0]

        # action, faite par l'algo, qui devra append à last_actions



if __name__ == "__main__":
    run = True
    while (run): ## point de retour en cas de fork
        print("start")
        client, nb, mapsize_x, mapsize_y = connect("127.0.0.1", 4242, "gigateam")
        if nb == 0:
            stderr.write("ko: no places in the team\n")
            exit(84)
        session = Session(client)
        client.inventory()
        print(session.client.recv().decode())
        # run = mainloop() # boucle principale (return en cas de fork)
