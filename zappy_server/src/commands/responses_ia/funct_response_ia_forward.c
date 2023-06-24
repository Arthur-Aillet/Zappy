/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_forward
*/

#include "zappy.h"

static void to_move_ia(ia_t *ia, common_t *com)
{
    if (ia->player->orientation == North) {
        ia->player->y -= 1;
        if (ia->player->y < 0)
            ia->player->y = com->gui->map.height - 1;
    }
    if (ia->player->orientation == Sud) {
        ia->player->y += 1;
        if (ia->player->y >= (int)com->gui->map.height)
            ia->player->y = 0;
    }
    if (ia->player->orientation == Est) {
        ia->player->x += 1;
        if (ia->player->x >= (int)com->gui->map.width)
            ia->player->x = 0;
    }
    if (ia->player->orientation == West) {
        ia->player->x -= 1;
        if (ia->player->x < 0)
            ia->player->x = com->gui->map.width - 1;
    }
}

void funct_response_ia_forward(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    (void)com;

    to_move_ia(ia, com);
    SIZE = 4;
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    OCTETS[0] = '\0';
    strcat(OCTETS, "ok\n\0");
    write(ia->buffer.sock.sockfd, OCTETS, SIZE);
    printf("%sPlayer: %s%d%s move to %s%d %d%s\n", P, R, ia->player->id, P, B,
            ia->player->x, ia->player->y, N);
}
