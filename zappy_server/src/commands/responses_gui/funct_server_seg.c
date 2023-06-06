/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_seg
*/

#include "zappy.h"

static team_t *to_find_team(uint8_t *n, common_t *common)
{
    for (int i = 0; i < common->nb_teams; i++) {
        for (int y = 0; y < common->teams[i].actif_player; y++) {
            if (atoi(n) == common->teams[i].players[y].id) {
                return &common->teams[i];
            }
        }
    }
    return NULL;
}

void funct_server_seg(uint8_t **args, gui_t *gui, common_t *common)
{
    team_t *tmp_team = to_find_team(args[0], common);

    if (tmp_team == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.usedSize = strlen(tmp_team->name) + 6;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    common->freq = atoi(args[0]);
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat(gui->buffer.bufferWrite.octets, "seg ");
    strcat(gui->buffer.bufferWrite.octets, tmp_team->name);
    strcat(gui->buffer.bufferWrite.octets, "\n\0");
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets, gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_seg\n");
}
