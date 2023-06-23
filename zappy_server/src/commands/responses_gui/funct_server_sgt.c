/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_sgt
*/

#include "zappy.h"
#include <string.h>
#include <stdlib.h>

void funct_server_sgt(char **args, void *info, common_t *common)
{
    (void)args;
    gui_t *gui = (gui_t *)info;
    char str_freq[20];

    sprintf(str_freq, "%ld", common->freq);
    gui->buffer.bufferWrite.usedSize = strlen(str_freq) + 6;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(char) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat(gui->buffer.bufferWrite.octets, "sgt ");
    strcat(gui->buffer.bufferWrite.octets, str_freq);
    strcat(gui->buffer.bufferWrite.octets, "\n\0");
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_sgt\n");
}
