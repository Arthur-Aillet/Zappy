/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_sst
*/

#include "zappy.h"
#include <string.h>

void funct_server_sst(char **args, void *info, common_t *com)
{
    gui_t *gui = (gui_t *)info;

    gui->buffer.bufferWrite.usedSize += 6;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    com->freq = atoi(args[0]);
    gui->buffer.bufferWrite.octets[0] = '\0';
    sprintf(gui->buffer.bufferWrite.octets, "sst %s\n", args[0]);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        strlen(gui->buffer.bufferWrite.octets));
    printf("rentrer dans la fonctions funct_server_sst\n");
}
