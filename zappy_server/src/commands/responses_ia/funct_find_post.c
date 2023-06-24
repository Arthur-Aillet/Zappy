/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_find_post
*/

#include "zappy.h"

static int find_post_egg(int tmp, common_t *com, ia_t *ia, int i)
{
    for (size_t j = 0; j < com->teams[i].nb_eggs; j++) {
        if (com->teams[i].egg[j].x == ia->player->x &&
            com->teams[i].egg[j].y == ia->player->y) {
            com->teams[i].egg = remove_egg(com->teams[i].egg[j],
                    com->teams[i].egg, com->teams[i].nb_eggs, com);
            com->teams[i].nb_eggs -= 1;
            tmp = 0;
        }
    }
    return tmp;
}

int find_post(common_t *com, ia_t *ia)
{
    int tmp = 1;

    for (size_t i = 0; i < MAX_PLAYER; i++) {
        if (com->ia[i].player == NULL)
            continue;
        if (com->ia[i].player->x != ia->player->x &&
            com->ia[i].player->y != ia->player->y) {
            remove_player(com->ia[i].player, ia->player, com);
            tmp = 0;
        }
    }
    for (size_t i = 0; i < com->nb_teams; i++) {
        tmp = find_post_egg(tmp, com, ia, i);
    }
    return tmp;
}
