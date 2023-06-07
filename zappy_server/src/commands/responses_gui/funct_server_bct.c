/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_bct
*/

#include "zappy.h"

void funct_server_bct(uint8_t **args, void *info, common_t *common)
{
    (void)common;
    char buffer_x[256];
    gui_t *gui = (gui_t *)info;
    gui->buffer.bufferWrite.usedSize = 6 + strlen((char*)args[0]) + strlen((char*)args[1]);
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "bct");
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[1]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    for (int i = 0; i < 7; i++) {
        sprintf(buffer_x, "%ld", gui->map.tiles[atoi((char*)args[0])][atoi((char*)args[1])].ressources[i]);
        gui->buffer.bufferWrite.usedSize += strlen(buffer_x) + 1;
        gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
        if (gui->buffer.bufferWrite.octets == NULL) {
            //error
            return;
        }
        strcat((char*)gui->buffer.bufferWrite.octets, buffer_x);
        strcat((char*)gui->buffer.bufferWrite.octets, " ");
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
    printf("rentrer dans la fonctions funct_server_bct\n");
}
