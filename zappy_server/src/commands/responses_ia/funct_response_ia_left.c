/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_left
*/

#include "zappy.h"

void funct_response_ia_left(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    (void)com;
    ia->player->orientation = (ia->player->orientation == North) ?
                                West : ia->player->orientation - 1;
    SIZE = 4;
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    OCTETS[0] = '\0';
    strcat(OCTETS, "ok\n\0");
    write(ia->buffer.sock.sockfd, OCTETS, SIZE);
    basic_log("rentrer dans la fonctions funct_response_ia_left", C, 0);
}
