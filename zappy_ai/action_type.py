## @package actionType
# This module defines the ActionType enum

##
## EPITECH PROJECT, 2022
## zappy [WSL: Ubuntu]
## File description:
## action_type.py
##

# Enum to define the last action made
class ActionType: #enum
    max = 5
    NONE = 0
    OK_ACTION = 1 # simple action just asking for an ok
    LOOK = 2
    INVENTORY  = 3
    CALL_ALL = 4
    FORK = 5

# action_time = [0, 1, 0.07, 0.07, 0.14, 40*0.07]
