/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_look_sud
*/

#include "zappy.h"

static void funct_complete_look_tile_sud(ia_t *ia, common_t *com,
                                    int nbr_tiles, int *post_tile)
{
    for (int tmp = 0; tmp < nbr_tiles; tmp++) {
        to_take_ressources_response_ia(ia, com, post_tile[0], post_tile[1]);
        post_tile[0] = (post_tile[0] - 1 < 0) ? (int)com->gui->map.width - 1 :
                                            post_tile[0] - 1;
    }
}

static void funct_response_look_sud_bis(ia_t *ia, common_t *com)
{
    int nbr_tiles = 0;
    int nbr_tiles_left = 0;
    int post_tile[2];

    post_tile[0] = 0;
    post_tile[1] = ia->player->y + 1;
    for (size_t level = 0; level < ia->player->level; level++) {
        nbr_tiles = 3 + level * 2;
        nbr_tiles_left = (nbr_tiles - 1) / 2;
        post_tile[0] = ia->player->x + nbr_tiles_left;
        if (post_tile[0] > (int)com->gui->map.width) {
            post_tile[0] = post_tile[0] % com->gui->map.width;
        }
        if (post_tile[1] == (int)com->gui->map.height) {
            post_tile[1] = 0;
        }
        funct_complete_look_tile_sud(ia, com, nbr_tiles, post_tile);
        post_tile[1] += 1;
    }
}

void funct_response_look_sud(ia_t *ia, common_t *com)
{
    SIZE = 2;
    OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
    if (OCTETS == NULL) {
        return;
    }
    OCTETS[0] = '\0';
    strcat(OCTETS, "[");
    to_take_ressources_response_ia(ia, com, ia->player->x, ia->player->y);
    funct_response_look_sud_bis(ia, com);
    OCTETS[SIZE - 2] = '\0';
    SIZE += 1;
    OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
    if (OCTETS == NULL) {
        return;
    }
    strcat(OCTETS, "]\n");
}
