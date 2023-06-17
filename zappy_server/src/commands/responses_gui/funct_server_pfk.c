/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pfk
*/

#include "zappy.h"

static team_t *to_find_team(uint8_t *n, common_t *common)
{
    for (size_t i = 0; i < common->nb_teams; i++) {
        for (size_t y = 0; y < common->teams[i].actif_player; y++) {
            if (atoi((char*)n) == common->teams[i].players[y].id) {
                return &common->teams[i];
            }
        }
    }
    return NULL;
}

static void to_lay_egg(team_t *team, ia_t *ia)
{
    team->egg = realloc(team->egg, sizeof(u_int8_t) * (team->nb_eggs + 1));
    if (team->egg == NULL) {
        //error
    }
    team->egg[team->nb_eggs] = set_egg(ia->player->x, ia->player->y);
    team->nb_eggs += 1;
}

void funct_server_pfk(uint8_t **args, void *info, common_t *common)
{
    ia_t *tmp_ia = to_find_ia(args[0], common);
    team_t *tmp_team = to_find_team(args[0], common);

    to_lay_egg(tmp_team, tmp_ia);
    if (tmp_ia == NULL) {
        //error
        return;
    }
    gui_t *gui = (gui_t *)info;
    gui->buffer.bufferWrite.usedSize = strlen((char*)args[0]) + 6;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "pfk ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets, gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pfk\n");
}
