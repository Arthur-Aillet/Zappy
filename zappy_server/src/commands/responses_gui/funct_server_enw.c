/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_enw
*/

#include "zappy.h"

static void funct_prepare_res(gui_t *gui, char **args,
                                char *buffer_x, char *buffer_y)
{
    gui->buffer.bufferWrite.usedSize = strlen(args[0]) +
    strlen(args[1]) + strlen(buffer_x) + strlen(buffer_y) + 9;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
    sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat(gui->buffer.bufferWrite.octets, "enw ");
    strcat(gui->buffer.bufferWrite.octets, args[0]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[1]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, buffer_x);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, buffer_y);
    strcat(gui->buffer.bufferWrite.octets, "\n\0");
}

void funct_server_enw(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);
    char buffer_x[256];
    char buffer_y[256];

    if (tmp_ia == NULL || gui == NULL) {
        return;
    }
    tmp_ia->player->inventory[EGG] -= 1;
    sprintf(buffer_x, "%d", tmp_ia->player->x);
    sprintf(buffer_y, "%d", tmp_ia->player->y);
    funct_prepare_res(gui, args, buffer_x, buffer_y);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_enw\n");
}
