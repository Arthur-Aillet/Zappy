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
    if (args[0] == NULL) {
        error("funct_response_ia_take_obj needs an argument", 0);
        return;
    }
    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                    sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL)
        return;
    ia->buffer.bufferWrite.octets[0] = '\0';
    if (strcmp((char*)args[0], "food") == 0) {
        response_take(ia, 0, com);
    } else {
        next_if_funct_take(ia, com, args);
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets,
        ia->buffer.bufferWrite.usedSize);
    basic_log("rentrer dans la fonctions funct_response_ia_take_obj", CYAN, 0);
}
