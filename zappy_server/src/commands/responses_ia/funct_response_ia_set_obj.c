/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_set_obj
*/

#include "zappy.h"

void funct_response_ia_set_obj(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    (void)com;
    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                    sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    ia->buffer.bufferWrite.octets[0] = '\0';
    printf("$%s$\n", (char*)args[0]);
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    } else if (strcmp((char*)args[0], "food") == 0) {
        response_set(ia, 0, com);
    } else {
        next_if_funct_set(ia, com, args);
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets,
        strlen((char*)ia->buffer.bufferWrite.octets));
    basic_log("rentrer dans la fonctions funct_response_ia_set_obj", C, 0);
}
