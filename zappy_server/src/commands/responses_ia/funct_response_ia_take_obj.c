/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_take_obj
*/

#include "zappy.h"

void funct_response_ia_take_obj(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    if (args[0] == NULL) {
        error("funct_response_ia_take_obj needs an argument", 0);
        return;
    }
    SIZE = 4;
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL)
        return;
    OCTETS[0] = '\0';
    if (strcmp(args[0], "food") == 0) {
        response_take(ia, 0, com);
    } else {
        next_if_funct_take(ia, com, args);
    }
    write(ia->buffer.sock.sockfd, OCTETS, SIZE);
    printf("%sPlayer: %s%d%s take an object%s\n", P, R, ia->player->id, P, N);
}
