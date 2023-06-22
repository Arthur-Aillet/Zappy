/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_tna
*/

#include "zappy.h"
#include <string.h>

static void funct_prepare_res(gui_t *gui, common_t *common)
{
    gui->buffer.bufferWrite.octets[0] = '\0';
    for (size_t nbr_teams = 0; nbr_teams < common->nb_teams; nbr_teams++) {
        gui->buffer.bufferWrite.usedSize += 5 +
                                strlen(common->teams[nbr_teams].name);
        gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets
        , sizeof(uint8_t) * (gui->buffer.bufferWrite.usedSize));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char*)gui->buffer.bufferWrite.octets, "tna");
        strcat((char*)gui->buffer.bufferWrite.octets, " ");
        strcat((char*)gui->buffer.bufferWrite.octets,
                common->teams[nbr_teams].name);
        strcat((char*)gui->buffer.bufferWrite.octets, "\n");
    }
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\0';
}

void funct_server_tna(uint8_t **args, void *info, common_t *common)
{
    (void)args;
    gui_t *gui = (gui_t *)info;

    gui->buffer.bufferWrite.usedSize = 1;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(uint8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    funct_prepare_res(gui, common);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_tna\n");
}
