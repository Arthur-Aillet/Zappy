/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pfk
*/

#include "zappy.h"

static void to_lay_egg(team_t *team, ia_t *ia)
{
    team->egg = realloc(team->egg, sizeof(u_int8_t) * (team->nb_eggs + 1));
    if (team->egg == NULL) {
        //error
    }
    team->egg[team->nb_eggs] = set_egg(ia->player->x, ia->player->y);
    team->nb_eggs += 1;
}

static void funct_prepare_response(gui_t *gui, uint8_t **args)
{
    gui->buffer.bufferWrite.usedSize = strlen((char*)args[0]) + 6;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                    sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "pfk ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
}

void funct_server_pfk(uint8_t **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);
    team_t *tmp_team;

    if (tmp_ia == NULL) {
        //error
        return;
    }
    tmp_team = to_find_team_by_uint8_t(args[0], common);
    if (tmp_team == NULL) {
        //error
        return;
    }
    to_lay_egg(tmp_team, tmp_ia);
    funct_prepare_response(gui, args);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
            gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pfk\n");
}
