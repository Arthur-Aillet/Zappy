## @package communication
# This module defines functions for all the AI clients to communicates via the same protocol
#
# This module is "proprietary" to this type of AI, does not defines universal functions to
# send messages to a server but only defines how the AI talk to themselves.

##
## EPITECH PROJECT, 2023
## zappy
## File description:
## communication.py
##

from server_action import broadcast
from datatypes import Creature
import re

class messageinfo:
    valid : bool = False
    text : str = ""
    id : int = -1
    number : int = 0
    direction: int = 0

def get_validation(message:str, creature: Creature):
    split = message.split("-")
    id = split[0]
    number = split[1]
    expected = -1
    for creature in creature.other_creatures:
        if creature.id == id:
            expected = creature.message_index
    if expected == -1:
        creature.other_creatures.append({"lvl": 0, "role": Creature.Types.BABY, "id": id, "messages": number})
    else:
        if expected - 2 <= number <= expected + 2:
            return id, number, True
        else:
            return id, number, False

def getmsginfo(message: str, creature: Creature):
    try:
        splitted = re.split(",||", message)
        result = messageinfo()
        result.direction = splitted[0].split(" ")[1]
        result.id, result.number, result.valid = get_validation(splitted[1], creature)
        result.text = splitted[2]
        return result
    except:
        return messageinfo()

def role_call(client, id, nb):
    """!
    Broadcasts a call for everyone to answer with its type of role for the queen to count.

    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "|" "role call" + " - " + "@everyone")

def move_to_base(client, id, nb, target):
    """!
    Broadcasts a call for everyone to answer with its type of role for the queen to count.

    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "|" + target + " come back here")


def change_profession(client, id, nb, target, type):
    """!
    Broadcasts a call for another ia to change their role

    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.
    @param taget id of the target
    @param type type to change to

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return(broadcast(client, str(id) + "-" + str(nb) + "|" + target + " deviens " + type + " - " + "et plus vite que ca"))

def status_report(client, id, nb, type, level):
    """!
    The AI will broadcast it's type and level.

    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.
    @param type type the AI is
    @param level level of the AI

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "|" + "my job is " + type + " " + level + " - " + "engagez vous qu'ils disaient")

def dict_to_str(dict: dict[str, int]):
    result = ""
    for key in dict :
        if key != "number" and key != "level" :
            result += "/" + dict[key] + " " + key
    return result

def str_to_dict(str: str):
    result : dict[str, int]
    split = str.split("/")
    for segment in split:
        result[segment.index] = {result.split(" ")[0], result.split(" ")[1]}
    return result

def take_this(client, id, nb, to_take: str):
    """!
    the AI orders another ia to pick up things

    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.
    @param to_take elements to take

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "|" + "it's dangerous to go alone take this:" + dict_to_str(str))

def enemy_spotted(client, id, nb, x, y):
    """!
    the AI tells others that it found a player

    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.
    @param x the x position of the target
    @param y the y position of the target

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "|" + "enemy spotted " + x + " " + y + " - " + "allez lui voler ses cailloux")

def base_moved(client, id, nb, x, y):
    """!
    the AI tells others that the base has moved

    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.
    @param x the x position of the target
    @param y the y position of the target

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "|" + "base moved to " + x + " " + y + " - " + "on demenage")

def dont_shoot(client, id, nb):
    """!
    the AI tells others that the base has moved

    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.
    @param x the x position of the target
    @param y the y position of the target

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "|" + "don't shoot")


def ask_for_info(client, id, nb):
    """!
    the AI tells others that it needs information
    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "|" + "need info" + " - " + "oh i have dementia? i dont remember asking!")

def give_info(client, id, nb, receiver_id, creature: Creature, orientation, type):
    """!
    the AI tells the asking one informations
    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.
    @param orientation wich way the receiving creature is facing
    @param type the type the receiving creature should be

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    new_id = len(creature.other_creatures)
    return broadcast(client, str(id) + "-" + str(nb) + "|" + "here's info " + receiver_id + " : " + creature.map.size_x + " " + creature.map.size_y + " " + orientation + " " + creature.spawn_pos_x + " " + creature.spawn_pos_y + " " + type + " " + new_id)

def parse_info(info: messageinfo, creature: Creature):
    split = messageinfo.text.split(" ")
    creature.map.size_x = split[4]
    creature.map.size_y = split[5]
    creature.orientation = split[6]
    creature.spawn_pos_x = split[7]
    creature.spawn_pos_y = split[8]
    creature.type = split[9]
    creature.id = split[10]

def ritual_in(client, id, nb, t):
    """!
    the AI tells the asking one informations
    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.
    @param t in how much time should the ritual begin

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "|" + "ritual in " + t + " - " + "autobots roll out")

def arrived(client, id, nb):
    """!
    the AI tells the asking one informations
    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "|" + "bien arrive")
