/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pin
*/

#include "zappy.h"

static ia_t *to_find_ia(uint8_t *n, common_t *common)
{
    for (int i = 0; i < common->nb_ia; i++) {
        if (atoi(n) == common->ia[i].player->id) {
            return &common->ia[i];
        }
    }
    return NULL;
}

void funct_server_pin(uint8_t **args, gui_t *gui, common_t *common)
{
    ia_t *tmp_ia = to_find_ia(args[0], common);

    if (tmp_ia == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.usedSize = 7 + strlen(args[0]) + strlen(args[1]) + strlen(args[2]);
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat(gui->buffer.bufferWrite.octets, "pin");
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[0]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[1]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[2]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    for (int i = 0; i < 7; i++) {
        gui->buffer.bufferWrite.usedSize += strlen(atoi(tmp_ia->player->inventory[i])) + 1;
        gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
        if (gui->buffer.bufferWrite.octets == NULL) {
            //error
            return;
        }
        strcat(gui->buffer.bufferWrite.octets, atoi(tmp_ia->player->inventory[i]));
        strcat(gui->buffer.bufferWrite.octets, " ");
    }
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\n';
    gui->buffer.bufferWrite.usedSize += 1;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\0';
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets, gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pin\n");
}
