/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_msz
*/

#include "zappy.h"

void funct_server_msz(uint8_t **args, gui_t *gui, common_t *common)
{
    char buffer_x[256];
    char buffer_y[256];

    sprintf(buffer_x, "%d", gui->map.width);
    sprintf(buffer_y, "%d", gui->map.height);
    gui->buffer.bufferWrite.usedSize = strlen(buffer_x) + strlen(buffer_y) + 7;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat(gui->buffer.bufferWrite.octets, "msz");
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, buffer_x);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, buffer_y);
    strcat(gui->buffer.bufferWrite.octets, "\n\0");
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets, gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_msz\n");
}
