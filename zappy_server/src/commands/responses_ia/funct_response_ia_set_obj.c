/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_set_obj
*/

#include "zappy.h"

void funct_response_ia_set_obj(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    (void)com;
    SIZE = 4;
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    OCTETS[0] = '\0';
    if (OCTETS == NULL) {
        return;
    } else if (strcmp(args[0], "food") == 0) {
        response_set(ia, 0, com);
    } else {
        next_if_funct_set(ia, com, args);
    }
    write(ia->buffer.sock.sockfd, OCTETS, strlen(OCTETS));
    printf("%sPlayer: %s%d%s set an object%s\n", P, R, ia->player->id, P, N);
}
