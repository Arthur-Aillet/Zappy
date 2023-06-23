/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_msz
*/

#include "zappy.h"

static void funct_prepare_res(gui_t *gui)
{
    char buffer_x[256];
    char buffer_y[256];

    sprintf(buffer_x, "%ld", gui->map.width);
    sprintf(buffer_y, "%ld", gui->map.height);
    gui->buffer.bufferWrite.usedSize = strlen(buffer_x) + strlen(buffer_y) + 7;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
    sizeof(uint8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "msz");
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, buffer_x);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, buffer_y);
    strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
}

void funct_server_msz(uint8_t **args, void *info, common_t *common)
{
    (void)common;
    (void)args;
    gui_t *gui = (gui_t *)info;

    funct_prepare_res(gui);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_msz\n");
}
