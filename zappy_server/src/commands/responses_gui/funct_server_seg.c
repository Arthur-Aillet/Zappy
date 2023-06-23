/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_seg
*/

#include "zappy.h"
#include <string.h>

static void funct_prepare_res(gui_t *gui, common_t *common,
                                team_t *tmp_team, char **args)
{
    gui->buffer.bufferWrite.usedSize = strlen(tmp_team->name) + 6;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
    sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    common->freq = atoi(args[0]);
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat(gui->buffer.bufferWrite.octets, "seg ");
    strcat(gui->buffer.bufferWrite.octets, tmp_team->name);
    strcat(gui->buffer.bufferWrite.octets, "\n\0");
}

static int to_check_in(team_t *tmp_team)
{
    int cmp = 0;

    for (size_t i = 0; i < tmp_team->actif_player; i++) {
        if (tmp_team->players[i].level == 8) {
            cmp++;
        }
    }
    if (cmp >= 6) {
        return 0;
    }
    return 1;
}

void funct_server_seg(char **args, void *info, common_t *common)
{
    ia_t *ia = (ia_t *)info;
    team_t *tmp_team = to_find_team_by_int(ia->player->id, common);

    if (tmp_team == NULL) {
        return;
    }
    if (to_check_in(tmp_team) == 1) {
        return;
    }
    funct_prepare_res(common->gui, common, tmp_team, args);
    write(common->gui->buffer.sock.sockfd,
    common->gui->buffer.bufferWrite.octets,
    common->gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_seg\n");
}
