/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pnw
*/

#include "zappy.h"

//toutes les données doivent etre envoyé dans args!!!! suit l'ordre dans le readme au niveau des arguments à renvoyer au gui

void funct_server_pnw(uint8_t **args, gui_t *gui, common_t *common)
{
    gui->buffer.bufferWrite.usedSize = strlen(args[0]) + strlen(args[1]) + strlen(args[2]) + strlen(args[3]) + strlen(args[4]) + strlen(args[5]) + 12;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets, sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat(gui->buffer.bufferWrite.octets, "pnw #");
    strcat(gui->buffer.bufferWrite.octets, args[0]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[1]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[3]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[4]);
    strcat(gui->buffer.bufferWrite.octets, " ");
    strcat(gui->buffer.bufferWrite.octets, args[5]);
    strcat(gui->buffer.bufferWrite.octets, "\n\0");
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets, gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pnw\n");
}
