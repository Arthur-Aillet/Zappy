/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pgt
*/

#include "zappy.h"
#include <string.h>

static void funct_prepare_res(gui_t *gui, char **args)
{
    gui->buffer.bufferWrite.usedSize += (strlen(args[1]) + 7);
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat(gui->buffer.bufferWrite.octets, "pgt ");
    strcat(gui->buffer.bufferWrite.octets, args[0]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[1]);
    strcat(gui->buffer.bufferWrite.octets, "\n\0");
}

void funct_server_pgt(char **args, void *info, common_t *common)
{
    ia_t *tmp_ia = to_find_ia(args[0], common);
    gui_t *gui = (gui_t *)info;

    if (tmp_ia == NULL) {
        return;
    }
    funct_prepare_res(gui, args);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        strlen(gui->buffer.bufferWrite.octets));
    printf("rentrer dans la fonctions funct_server_pgt\n");
}
