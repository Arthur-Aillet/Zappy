/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_left
*/

#include "zappy.h"

void funct_response_ia_left(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    (void)com;
    ia->player->orientation = (ia->player->orientation == North) ?
                                West : ia->player->orientation - 1;
    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)ia->buffer.bufferWrite.octets, "ok\n\0");
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets,
    ia->buffer.bufferWrite.usedSize);
    basic_log("rentrer dans la fonctions funct_response_ia_left", CYAN, 0);
}
