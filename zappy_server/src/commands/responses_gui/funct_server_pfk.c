/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pfk
*/

#include "zappy.h"

static void funct_prepare_res(gui_t *gui, char **args)
{
    gui->buffer.bufferWrite.usedSize = strlen(args[0]) + 6;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                    sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat(gui->buffer.bufferWrite.octets, "pfk ");
    strcat(gui->buffer.bufferWrite.octets, args[0]);
    strcat(gui->buffer.bufferWrite.octets, "\n\0");
}

void funct_server_pfk(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);
    team_t *tmp_team;

    if (tmp_ia == NULL) {
        return;
    }
    tmp_team = to_find_team_by_uint8_t(args[0], common);
    if (tmp_team == NULL) {
        return;
    }
    funct_prepare_res(gui, args);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
            gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pfk\n");
}
