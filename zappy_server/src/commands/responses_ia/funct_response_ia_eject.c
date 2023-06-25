/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_eject
*/

#include "zappy.h"

void funct_response_ia_eject(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    char buffer_ennemy[256];

    SIZE = 4;
    args = malloc(sizeof(char *) * 2);
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL || args == NULL)
        return;
    OCTETS[0] = '\0';
    sprintf(buffer_ennemy, "%d", ia->player->id);
    args[0] = malloc(sizeof(char) * (strlen(buffer_ennemy) + 1));
    if (args[0] == NULL)
        return;
    args[0][0] = '\0';
    args[1] = NULL;
    strcat(args[0], buffer_ennemy);
    if (find_post(com, ia) == 0) {
        strcat(OCTETS, "ok\n\0");
    } else {
        strcat(OCTETS, "ko\n\0");
    }
    funct_server_pex(args, com->gui, com);
    write(ia->buffer.sock.sockfd, OCTETS, SIZE);
    printf("%sPlayer: %s%d%s Eject%s\n", P, R, ia->player->id, P, N);
    free_array((void **)args);
}
