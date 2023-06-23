/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_look_player
*/

#include "zappy.h"

static void to_take_ressources_response_ia_player(player_t *player, ia_t *ia,
                                                 int *pos)
{
    if (player->x == pos[0] && player->y == pos[1]) {
        SIZE += 7;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "player ");
    }
}

static void to_take_ressources_response_ia_egg(int *pos, int *post_tmp,
                                                ia_t *ia, common_t *com)
{
    if (com->teams[post_tmp[0]].egg[post_tmp[1]].x == pos[0] &&
        com->teams[post_tmp[0]].egg[post_tmp[1]].y == pos[1]) {
        SIZE += 4;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "egg ");
    }
}

static void to_take_ressources_response_ia_bis(ia_t *ia,
                                        common_t *com, int x, int y)
{
    int pos[2];
    int post_tmp[2];

    pos[0] = x;
    pos[1] = y;
    for (size_t i = 0; i < com->nb_teams; i++) {
        for (size_t j = 0; j < com->teams[i].nb_eggs; j++) {
            post_tmp[0] = i;
            post_tmp[1] = j;
            to_take_ressources_response_ia_egg(pos, post_tmp, ia, com);
        }
    }
    to_take_ressources_response_ia_food(ia, com, x, y);
}

void to_take_ressources_response_ia(ia_t *ia, common_t *com,
                                                int x, int y)
{
    int pos[2];

    pos[0] = x;
    pos[1] = y;
    for (size_t j = 0; j < MAX_PLAYER; j++) {
        if (com->ia[j].player == NULL)
            continue;
        to_take_ressources_response_ia_player(com->ia[j].player, ia, pos);
    }
    to_take_ressources_response_ia_bis(ia, com, x, y);
}
