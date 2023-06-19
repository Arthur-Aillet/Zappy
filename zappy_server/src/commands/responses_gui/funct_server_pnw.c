/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pnw
*/

#include "zappy.h"
#include <string.h>

static void funct_prepare_response(gui_t *gui, uint8_t **args)
{
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
    sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "pnw #");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[1]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[3]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[4]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[5]);
    strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
}

void funct_server_pnw(uint8_t **args, void *info, common_t *common)
{
    (void)common;
    gui_t *gui = (gui_t *)info;

    gui->buffer.bufferWrite.usedSize = strlen((char*)args[0]) +
    strlen((char*)args[1]) + strlen((char*)args[2]) + strlen((char*)args[3]) +
    strlen((char*)args[4]) + strlen((char*)args[5]) + 12;
    funct_prepare_response(gui, args);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pnw\n");
}
