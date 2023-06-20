/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** client_undefined.c
*/

#include "zappy.h"
#include <string.h>

static int check_teams_name(const char *team_name, common_t *com, int idx)
{
    for (size_t i = 0; i < com->nb_teams; i++) {
        if (strcmp(TEAM(i).name, team_name) == 0)
            check_slot_and_create_player(com, i, idx);
    }
    return 0;
}

static int check_graphic(uint8_t **command, common_t *com, int idx)
{
    if (strcmp((char*)command[0], "GRAPHIC") != 0 || command[1] != NULL)
        return 0;
    com->client[idx].type = GUI;
    com->client[idx].str_cli = (gui_t *) &(com->gui);
    com->gui->buffer.sock.sockfd = com->client[idx].socket;
    com->gui->buffer.sock.addr = com->client[idx].addr;
    return 1;
}

int undefined_client_command(uint8_t **command, common_t *com, int idx)
{
    if (check_graphic(command, com, idx) == 1) {
        //TODO - send command msz
        //TODO - send command sgt
        //TODO - send command bct for all tiles
        write(com->client[idx].socket, "graphic command\n", 16);
    } else if (check_teams_name((char*)command[0], com, idx) == 1){
        write(com->client[idx].socket, "player command\n", 15);
        //TODO - send client num `TEAM(i).nb_slot`
        //TODO - send world's dimension
    } else {
        return error("Invalid command for defined the client", 0);
    }
    return 1;
}
