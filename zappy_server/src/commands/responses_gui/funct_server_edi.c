/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_edi
*/

#include "zappy.h"

//appeler si un oeuf est ejecter d'une case

void funct_server_edi(uint8_t **args, void *info, common_t *common)
{
    (void)common;
    gui_t *gui = (gui_t *)info;

    gui->buffer.bufferWrite.usedSize = strlen((char*)args[0]) + 6;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                sizeof(uint8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "edi ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_edi\n");
}
