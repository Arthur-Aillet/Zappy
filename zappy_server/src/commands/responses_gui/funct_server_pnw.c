/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pnw
*/

#include "zappy.h"
#include <string.h>

static void funct_prepare_res(gui_t *gui, char **args)
{
    free(gui->buffer.bufferWrite.octets);
    gui->buffer.bufferWrite.octets = malloc(sizeof(char) *
    (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat(gui->buffer.bufferWrite.octets, "pnw #");
    strcat(gui->buffer.bufferWrite.octets, args[0]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[1]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[2]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[3]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[4]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[5]);
    strcat(gui->buffer.bufferWrite.octets, "\n\0");
}

void funct_server_pnw(char **args, void *info, common_t *common)
{
    (void)common;
    gui_t *gui = (gui_t *)info;

    gui->buffer.bufferWrite.usedSize = strlen(args[0]) +
    strlen(args[1]) + strlen(args[2]) + strlen(args[3]) +
    strlen(args[4]) + strlen(args[5]) + 12;
    funct_prepare_res(gui, args);
    gui->buffer.bufferWrite.usedSize =
    strlen(gui->buffer.bufferWrite.octets);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    basic_log("Send pnw command tout the GUI", C, 0);
}
