/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_seg
*/

#include "zappy.h"
#include <string.h>

static void funct_prepare_response(gui_t *gui, common_t *common,
                                team_t *tmp_team, uint8_t **args)
{
    gui->buffer.bufferWrite.usedSize = strlen(tmp_team->name) + 6;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
    sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    common->freq = atoi((char*)args[0]);
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "seg ");
    strcat((char*)gui->buffer.bufferWrite.octets, tmp_team->name);
    strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
}

void funct_server_seg(uint8_t **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    team_t *tmp_team = to_find_team_by_uint8_t(args[0], common);

    if (tmp_team == NULL) {
        return;
    }
    funct_prepare_response(gui, common, tmp_team, args);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
    gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_seg\n");
}
