/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_look_est
*/

#include "zappy.h"

static void funct_complete_look_tile_est(ia_t *ia, common_t *com,
                                    int nbr_tiles, int *post_tile)
{
    for (int tmp = 0; tmp < nbr_tiles; tmp++) {
        to_take_ressources_response_ia(ia, com,
                                    post_tile[0], post_tile[1]);
        post_tile[1] = (post_tile[1] + 1 == (int)com->gui->map.height) ? 0 :
                                            post_tile[1] + 1;
    }
}

static void funct_response_look_est_bis(ia_t *ia, common_t *com)
{
    int nbr_tiles = 0;
    int nbr_tiles_left = 0;
    int post_tile[2];

    post_tile[0] = ia->player->x + 1;
    post_tile[1] = 0;
    for (size_t level = 0; level < ia->player->level; level++) {
        nbr_tiles = 3 + level * 2;
        printf("%snbr_tiles: %d%s\n", P, nbr_tiles, N);
        nbr_tiles_left = (nbr_tiles - 1) / 2;
        printf("%snbr_tiles_left: %d%s\n", P, nbr_tiles_left, N);
        post_tile[1] = ia->player->y - nbr_tiles_left;
        if (post_tile[0] > (int)com->gui->map.width) {
            post_tile[0] = 0;
        }
        if (post_tile[1] < 0) {
            post_tile[1] = com->gui->map.height + post_tile[1];
        }
        funct_complete_look_tile_est(ia, com, nbr_tiles, post_tile);
        post_tile[0] += 1;
    }
}

void funct_response_look_est(ia_t *ia, common_t *com)
{
    ia->buffer.bufferWrite.usedSize = 2;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat((char *)ia->buffer.bufferWrite.octets, "[");
    to_take_ressources_response_ia(ia, com, ia->player->x, ia->player->y);
    funct_response_look_est_bis(ia, com);
    printf("usedSize: %ld\n", ia->buffer.bufferWrite.usedSize);
    ia->buffer.bufferWrite.usedSize += 2;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    printf("usedSize: %ld\n", ia->buffer.bufferWrite.usedSize);
    printf("size: %ld", strlen((char*)ia->buffer.bufferWrite.octets));
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize - 5] = ']';
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize - 4] = '\0';
}
