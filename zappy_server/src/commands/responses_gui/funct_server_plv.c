/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_plv
*/

#include "zappy.h"
#include <string.h>
#include <stdlib.h>

static void funct_prepare_res(gui_t *gui, ia_t *tmp_ia, uint8_t **args)
{
    char str_level[3];

    sprintf(str_level, "%ld", tmp_ia->player->level);
    gui->buffer.bufferWrite.usedSize += (strlen(str_level) + 7);
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(uint8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    sprintf((char*)gui->buffer.bufferWrite.octets, "plv %s %s\n",
                                    (char*)args[0], str_level);
}

void funct_server_plv(uint8_t **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);

    if (tmp_ia == NULL) {
        return;
    }
    funct_prepare_res(gui, tmp_ia, args);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        strlen((char*)gui->buffer.bufferWrite.octets));
    printf("rentrer dans la fonctions funct_server_plv\n");
}
