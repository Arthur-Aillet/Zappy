/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pfk
*/

#include "zappy.h"

//voir avec ludo pour les oeufs comment ça se gere dans nos structures!!!

void funct_server_pfk(uint8_t **args, void *info, common_t *common)
{
    ia_t *tmp_ia = to_find_ia(args[0], common);

    if (tmp_ia == NULL) {
        //error
        return;
    }
    gui_t *gui = (gui_t *)info;
    gui->buffer.bufferWrite.usedSize = strlen((char*)args[0]) + 6;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "pfk ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets, gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pfk\n");
}
