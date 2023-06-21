/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_take_obj
*/

#include "zappy.h"

void funct_response_ia_take_obj(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                    sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    ia->buffer.bufferWrite.octets[0] = '\0';
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    } else if (strcmp((char*)args[0], "FOOD")) {
        response_take(ia, 0, com);
    } else {
        next_if_funct_take(ia, com, args);
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets,
        ia->buffer.bufferWrite.usedSize);
    basic_log("rentrer dans la fonctions funct_response_ia_take_obj", CYAN, 0);
}
