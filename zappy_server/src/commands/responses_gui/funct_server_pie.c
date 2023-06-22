/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pie
*/

#include "zappy.h"

void funct_server_pie(uint8_t **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;

    (void)common;
    gui->buffer.bufferWrite.usedSize = strlen((char*)args[0]) +
                    strlen((char*)args[1]) + strlen((char*)args[2]) + 8;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "pie ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[1]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[2]);
    strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pie\n");
}
