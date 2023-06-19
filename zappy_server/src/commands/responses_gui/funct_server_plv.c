/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_plv
*/

#include "zappy.h"
#include <string.h>
#include <stdlib.h>

static void funct_prepare_response(gui_t *gui, ia_t *tmp_ia, uint8_t **args)
{
    char str_level[3];

    sprintf(str_level, "%ld", tmp_ia->player->level);
    gui->buffer.bufferWrite.usedSize += (strlen(str_level) + 7);
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "plv ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, str_level);
    strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
}

void funct_server_plv(uint8_t **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);

    if (tmp_ia == NULL) {
        return;
    }
    funct_prepare_response(gui, tmp_ia, args);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_plv\n");
}
