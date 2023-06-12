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

def call_all(client, id, nb):
    """!
    Broadcasts a call for everyone to answer with its type of role for the queen to count.

    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "-@everyone")

def say_type(client, id, nb):
    """!
    The AI will broadcast it's type.

    Often used in answer to a call_all(client, id, nb)

    @param client Socket client of the AI
    @param id AI id.
    @param nb Number of messages already sent by this AI to counter spam attacks. Need to be
    incremented by one every time by the caller or others will ignore its messages.

    @return Return the value returned by the broadcast(client, text) function (that return the
    succes or fail of the send_server function with True or False).
    """
    return broadcast(client, str(id) + "-" + str(nb) + "-@everyone")
