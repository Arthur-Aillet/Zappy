/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** choose_command.c
*/

#include "zappy.h"

//NOTE - functions return 1 if successful and 0 otherwise

static int command_ia_part_ones(uint8_t **cmd, common_t *com, int i)
{
    (void)com;
    (void)i;
    if (strcmp((char*)cmd[0], "Forward") == 0) {
        printf("Forward\n");
        return 1;
    }
    if (strcmp((char*)cmd[0], "Right") == 0) {
        printf("Right\n");
        return 1;
    }
    if (strcmp((char*)cmd[0], "Left") == 0) {
        printf("Left\n");
        return 1;
    }
    if (strcmp((char*)cmd[0], "Look") == 0) {
        printf("Look\n");
        return 1;
    }
    if (strcmp((char*)cmd[0], "Inventory") == 0) {
        printf("Inventory\n");
        return 1;
    }
    if (strcmp((char*)cmd[0], "Broadcast") == 0) {
        printf("Broadcast\n");
        return 1;
    }
    return 0;
}

static int command_ia_part_two(uint8_t **cmd, common_t *com, int i)
{
    (void)com;
    (void)i;
    if (strcmp((char*)cmd[0], "Fork") == 0) {
        printf("Fork\n");
        return 1;
    }
    if (strcmp((char*)cmd[0], "Eject") == 0) {
        printf("Eject\n");
        return 1;
    }
    if (strcmp((char*)cmd[0], "Take") == 0) {
        printf("Take\n");
        return 1;
    }
    if (strcmp((char*)cmd[0], "Set") == 0) {
        printf("Set\n");
        return 1;
    }
    if (strcmp((char*)cmd[0], "Incantation") == 0) {
        printf("Incantation\n");
        return 1;
    }
    if (strcmp((char*)cmd[0], "Connect_nbr") == 0) {
        printf("Connect_nbr\n");
        return 1;
    }
    return 0;
}

int choose_ia_command(uint8_t **cmd, common_t *com, int i)
{
    if (command_ia_part_ones(cmd, com, i) == 1) {
        return 1;
    } else if (command_ia_part_two(cmd, com, i) == 1) {
        return 1;
    } else {
        return error("Unknown command", 0);
    }
}

int choose_graphic_command(uint8_t **cmd, common_t *com, int i)
{
    (void)com;
    (void)i;
    if (strcmp((char*)cmd[0], "msz") == 0) {
        printf("msz\n");
    } else if (strcmp((char*)cmd[0], "bct") == 0) {
        printf("bct\n");
    } else if (strcmp((char*)cmd[0], "mct") == 0) {
        printf("mct\n");
    } else if (strcmp((char*)cmd[0], "tna") == 0) {
        printf("tna\n");
    } else if (strcmp((char*)cmd[0], "ppo") == 0) {
        printf("ppo\n");
    } else if (strcmp((char*)cmd[0], "plv") == 0) {
        printf("plv\n");
    } else if (strcmp((char*)cmd[0], "pin") == 0) {
        printf("pin\n");
    } else if (strcmp((char*)cmd[0], "sgt") == 0) {
        printf("sgt\n");
    } else if (strcmp((char*)cmd[0], "sst") == 0) {
        printf("sst\n");
    } else
        return error("Unknown command", 0);
    return 1;
}
