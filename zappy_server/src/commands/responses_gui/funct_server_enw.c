/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_enw
*/

#include "zappy.h"

//"enw (e) (comment le trouver le e) n X Y\n"

static ia_t *to_find_ia(uint8_t *n, common_t *common)
{
    for (int i = 0; i < common->nb_ia; i++) {
        if (atoi(n) == common->ia[i].player->id) {
            return &common->ia[i];
        }
    }
    return NULL;
}

void funct_server_enw(uint8_t **args, gui_t *gui, common_t *common)
{
    ia_t *tmp_ia = to_find_ia(args[0], common);
    char buffer_x[256];
    char buffer_y[256];

    if (tmp_ia == NULL) {
        //error
        return;
    }
    tmp_ia->player->inventory[EGG] -= 1;
    sprintf(buffer_x, "%d", tmp_ia->player->x);
    sprintf(buffer_y, "%d", tmp_ia->player->y);
    gui->buffer.bufferWrite.usedSize = strlen(args[0]) + strlen(args[1]) + strlen(buffer_x) + strlen(buffer_y) + 9;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
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
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets, gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_enw\n");
}
