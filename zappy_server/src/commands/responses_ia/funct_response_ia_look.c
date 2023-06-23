/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_look
*/

#include "zappy.h"

void funct_response_ia_look(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    switch (ia->player->orientation) {
        case North:
            funct_response_look_north(ia, com);
            break;
        case Est:
            funct_response_look_est(ia, com);
            break;
        case Sud:
            funct_response_look_sud(ia, com);
            break;
        default:
            funct_response_look_west(ia, com);
    }
    write(ia->buffer.sock.sockfd, OCTETS, strlen(OCTETS));
    printf("rentrer dans la fonctions funct_response_ia_look\n");
}
