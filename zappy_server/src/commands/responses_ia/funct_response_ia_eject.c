/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_eject
*/

#include "zappy.h"

static void eject_response(common_t *com, ia_t *ia)
{
    SIZE = 4;
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL)
        return;
    OCTETS[0] = '\0';
    if (find_post(com, ia) == 0) {
        strcat(OCTETS, "ok\n\0");
    } else {
        strcat(OCTETS, "ko\n\0");
    }
    write(ia->buffer.sock.sockfd, OCTETS, SIZE);
}

void funct_response_ia_eject(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    char buffer_ennemy[256];

    args = malloc(sizeof(char *) * 2);
    if (args == NULL)
        return;
    sprintf(buffer_ennemy, "%d", ia->player->id);
    args[0] = malloc(sizeof(char) * (strlen(buffer_ennemy) + 1));
    if (args[0] == NULL)
        return;
    args[0][0] = '\0';
    args[1] = NULL;
    strcat(args[0], buffer_ennemy);
    eject_response(com, ia);
    funct_server_pex(args, com->gui, com);
    printf("%sPlayer: %s%d%s Eject%s\n", P, R, ia->player->id, P, N);
    free_array((void **)args);
}
