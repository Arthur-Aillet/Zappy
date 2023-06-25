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
        if (strcmp(TEAM(i).name, team_name) == 0 &&
            (TEAM(i).nb_slot - TEAM(i).actif_player) > 0)
            return check_slot_and_create_player(com, i, idx);
    }
    return 0;
}

static int check_graphic(char **command, common_t *com, int idx)
{
    if (strcmp(command[0], "GRAPHIC") != 0 || command[1] != NULL)
        return 0;
    com->client[idx].type = GUI;
    com->client[idx].str_cli = (gui_t *) &(com->gui);
    com->gui->buffer.sock.sockfd = com->client[idx].socket;
    com->gui->buffer.sock.addr = com->client[idx].addr;
    return 1;
}

static void response_start_ia(client_t client, common_t *com)
{
    char buffer_x[256];
    char buffer_y[256];
    char buffer_nb_slot[256];
    int size = 0;
    char *response;
    player_t *player = (player_t *)client.str_cli;

    sprintf(buffer_nb_slot, "%ld",
    to_find_team_by_int(player->id, com)->nb_slot);
    sprintf(buffer_x, "%ld", com->gui->map.width);
    sprintf(buffer_y, "%ld", com->gui->map.height);
    size = strlen(buffer_nb_slot) + strlen(buffer_x) + strlen(buffer_y) + 4;
    response = malloc(sizeof(char) * size);
    if (response == NULL) {
        return;
    }
    response[0] = '\0';
    sprintf(response, "%s\n%s %s\n", buffer_nb_slot, buffer_x, buffer_y);
    write(client.socket, response, strlen(response));
    free(response);
}

int undefined_client_command(char **command, common_t *com, int idx)
{
    if (check_graphic(command, com, idx) == 1) {
        funct_server_msz(NULL, com->gui, com);
        funct_server_sgt(NULL, com->gui, com);
        funct_server_all_bct(NULL, com->gui, com);
    } else if (check_teams_name(command[0], com, idx) == 1){
        response_start_ia(com->client[idx], com);
    } else {
        return error("Invalid command for defined the client", 0);
    }
    return 1;
}
