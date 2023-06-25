#!/usr/bin/env python3
##
## EPITECH PROJECT, 2023
## zappy
## File description:
## zappy_ai
##

import socket
from connect import connect
from communication import getmsginfo
from server_get import *
from server_action import *
from sys import stderr
from action_type import ActionType
from datatypes import Session, Creature
from communication import *
from gatherer_loop import gatherer_loop
from queen_loop import queen_loop, take_new_role_in_account
from warrior_loop import warrior_loop
from butler_loop import butler_loop
from common import *

def mainloop(ai: Session): # mainloop peut return True si elle est enfant de fork / false si stop
    """!
    The function mainloop will run the main algorithm of the AI.
    The loop is made like so :
    Reception :
        reception of incoming messages of all types from the server.
        The algorithm stores what actions it made to expect answers from the server.
        By example, if it sent a command asking for the inventory, it knows that the next hypotetic
        answer from the server is an inventory, and can parse it.
        The mainloop function also accepts unexpected messages from the server, like incomming broadcasts,
        that need to be processed too.
    Action :
        The reception part updates all needed values in the Session object.
        The action part will launch if needed all actions functions from the algorithm
    Fork :
        A special type of action, fork. It allow the AI to replicate itself on an egg.
        The parent part can continue the loop.
        The child part need to return True, it will restart the program loop and reset values
    Quit :
        Return False to quit.

    @param ai AI Session

    @return a boolean value.
    """
    looping = True
    last_actions = []
    creature = Creature()
    message = ""
    invtimer = 0
    communication : messageinfo()
    while looping:
        try:
            message = ai.client.recv(1024).decode() # peut être mettre un timeout pour éviter de rester perdu sur une interrupt de co
            print("got message :", message)
        except socket.timeout:
            # err = e.args[0]
            # this next if/else is a bit redundant, but illustrates how the
            # timeout exception is setup
            print ('(recv timed out)')
        except socket.error:
            # Something else happened, handle error, exit, etc.
            print("socket error")
            return False
        else:
            if len(message) == 0:
                print ('server shutdown')
                return False

        # gestion des envois inopinés du serveur
        if message == "dead":
            print("dead !")
            return False
        if message.startswith("Message "):
            communication : messageinfo = getmsginfo(message, creature)

        if communication.valid:
            if communication.text.startswith("role call"):
                status_report(ai.client, creature.id, creature.message_index, creature.type, creature.level)
                creature.message_index += 1
            if communication.text.__contains__(" deviens "):
                change_split = communication.text.split(" ")
                if creature.id == change_split[0] :
                    if change_split [2] == 0:
                        creature.type = Creature.Types.QUEEN
                    if change_split [2] == 1:
                        creature.type = Creature.Types.BABY
                    if change_split [2] == 2:
                        creature.type = Creature.Types.BUTLER
                    if change_split [2] == 3:
                        creature.type = Creature.Types.GATHERER
                    if change_split [2] == 4:
                        creature.type = Creature.Types.WARRIOR
            if communication.text.__contains__("come back here"):
                come_split = communication.text.split(" ")
                if creature.id == come_split[0]:
                    go_to_base(creature, ai, last_actions)
            if communication.text.startswith("it's dangerous"):
                pick_up_list(str_to_dict(communication.text.split(":")[1]), last_actions, ai)
            if communication.text.startswith("enemy spotted"):
                enemy_split = communication.text.split(" ")
                enemy_x = enemy_split[2]
                enemy_y = enemy_split[3]
                if enemy_x == creature.pos_x and enemy_y == creature.pos_y:
                    dont_shoot(ai.client, creature.id, creature.message_index)
                    creature.message_index += 1
            if communication.text.startswith("base moved to"):
                move_split = communication.text.split(" ")
                creature.spawn_pos_x = move_split[3]
                creature.spawn_pos_y = move_split[4]
            if communication.text.startswith("ritual in"):
                creature.time_to_ritual = communication.text.split(" ")[2]
            if communication.text.startswith("my job is "):
                take_new_role_in_account(communication, creature)
            continue # traiter le maissage

        creature.looked = False
        if invtimer % 10 == 0:
            last_actions.append(inventory(ai.client))


        # gestion des envois prévus du serveur (si une récéption est prévue)
        if (not message == "") and len(last_actions) == 0:
            continue
        if (not message == "") and last_actions[0] == ActionType.NONE:
            last_actions.pop(0)
            continue
        if (last_actions[0] == ActionType.INVENTORY):
            last_actions.pop(0)
            creature.inventory = parse_inventory(message)
            continue
        if last_actions[0] == ActionType.LOOK:
            last_actions.pop(0)
            creature.last_look = parse_look(message)
            creature.looked = True
            continue

        if creature.time_to_ritual == 0:
            send_server(ai.client, "Incantation\n")
            creature.level += 1
        if creature.time_to_ritual >= 0 :
            creature.time_to_ritual -= 1;
        if (creature.type == Creature.Types.QUEEN) :
            queen_loop(creature, last_actions, session)
        if creature.type == Creature.Types.BABY:
            creature.var += 1
            if creature.var >= 15:
                creature.type = Creature.Types.QUEEN
            ask_for_info(ai.client, -1, creature.message_index)
            if messageinfo.valid and messageinfo.text.startswith("here's info"):
                parse_info(messageinfo, creature)
        if (creature.type == Creature.Types.BUTLER) :
            butler_loop(creature, last_actions, session)
        if (creature.type == Creature.Types.GATHERER) :
            gatherer_loop(creature, last_actions, session)
        if (creature.type == Creature.Types.WARRIOR) :
            warrior_loop(creature, last_actions, session)
        # traitement de tous les cas de reception en fonction de last_action[0]

        # action, faite par l'algo, qui devra append à last_actions

if __name__ == "__main__":
    run = True
    while (run): ## point de retour en cas de fork
        print("start")
        try:
            client, nb, mapsize_x, mapsize_y = connect("127.0.0.1", 4444, "Team1")
        except:
            print("connection refused")
            exit(84)
        if nb == 0:
            stderr.write("ko: no places in the team\n")
            exit(84)
        session = Session(client)
        run = mainloop(session) # boucle principale (return en cas de fork)
