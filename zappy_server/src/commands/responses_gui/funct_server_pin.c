/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pin
*/

#include "zappy.h"
#include <string.h>
#include <stdlib.h>

void funct_server_pin(uint8_t **args, void *info, common_t *common)
{
    ia_t *tmp_ia = to_find_ia(args[0], common);

    if (tmp_ia == NULL) {
        //error
        return;
    }
    gui_t *gui = (gui_t *)info;
    gui->buffer.bufferWrite.usedSize = 7 +  + strlen((char*)args[1]) + strlen((char*)args[2]);
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "pin");
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[1]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[2]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    for (int i = 0; i < 7; i++) {
        char str_ressource[20];
        sprintf(str_ressource, "%ld", tmp_ia->player->inventory[i]);
        gui->buffer.bufferWrite.usedSize += strlen(str_ressource) + 1;
        gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
        if (gui->buffer.bufferWrite.octets == NULL) {
            //error
            return;
        }
        strcat((char*)gui->buffer.bufferWrite.octets, str_ressource);
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
    printf("rentrer dans la fonctions funct_server_pin\n");
}
