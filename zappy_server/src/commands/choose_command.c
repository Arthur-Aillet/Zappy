/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** choose_command.c
*/

#include "zappy.h"

int choose_ia_command(uint8_t **cmd, common_t *com, int i)
{
    if (strcmp((char*)cmd[0], "Forward") == 0) {
        printf("Forward\n");
    } else if (strcmp((char*)cmd[0], "Right") == 0) {
        printf("Right\n");
    } else if (strcmp((char*)cmd[0], "Left") == 0) {
        printf("Left\n");
    } else if (strcmp((char*)cmd[0], "Look") == 0) {
        printf("Look\n");
    } else if (strcmp((char*)cmd[0], "Inventory") == 0) {
        printf("Inventory\n");
    } else if (strcmp((char*)cmd[0], "Broadcast") == 0) {
        printf("Broadcast\n");
    } else if (strcmp((char*)cmd[0], "Connect_nbr") == 0) {
        printf("Connect_nbr\n");
    } else if (strcmp((char*)cmd[0], "Fork") == 0) {
        printf("Fork\n");
    } else if (strcmp((char*)cmd[0], "Eject") == 0) {
        printf("Eject\n");
    } else if (strcmp((char*)cmd[0], "Take") == 0) {
        printf("Take\n");
    } else if (strcmp((char*)cmd[0], "Set") == 0) {
        printf("Set\n");
    } else if (strcmp((char*)cmd[0], "Incantation") == 0) {
        printf("Incantation\n");
    } else {
        return error("Unknown command", 0);
    }
    return 1;
}

int choose_graphic_command(uint8_t **cmd, common_t *com, int i)
{
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
    } else {
        return error("Unknown command", 0);
    }
    return 1;
}
