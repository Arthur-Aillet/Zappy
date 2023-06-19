/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_sgt
*/

#include "zappy.h"
#include <string.h>
#include <stdlib.h>

void funct_server_sgt(uint8_t **args, void *info, common_t *common)
{
    (void)args;
    gui_t *gui = (gui_t *)info;
    char str_freq[20];

    sprintf(str_freq, "%ld", common->freq);
    gui->buffer.bufferWrite.usedSize = strlen(str_freq) + 6;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "sgt ");
    strcat((char*)gui->buffer.bufferWrite.octets, str_freq);
    strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_sgt\n");
}
