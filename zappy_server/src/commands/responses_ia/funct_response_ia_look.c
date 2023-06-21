/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_look
*/

#include "zappy.h"

//voir les differentes evolution d'un joueur pour son champs de vision

static void to_take_ressources_response_ia(ia_t *ia, common_t *com, int x, int y)
{
    for (size_t i = 0; i < com->nb_teams; i++) {
        for (size_t j = 0; j < com->teams[i].actif_player; j++) {
            if (com->teams[i].players[j].x == x && com->teams[i].players[j].y == y) {
                ia->buffer.bufferWrite.usedSize += 7;
                ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                                sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
                if (ia->buffer.bufferWrite.octets == NULL) {
                    return;
                }
                ia->buffer.bufferWrite.octets = (u_int8_t *)strcat((char *)ia->buffer.bufferWrite.octets, "player ");
            }
        }
    }
    for (size_t i = 0; i < com->nb_teams; i++) {
        for (size_t j = 0; j < com->teams[i].nb_eggs; j++) {
            if (com->teams[i].egg[j].x == x && com->teams[i].egg[j].y == y) {
                ia->buffer.bufferWrite.usedSize += 4;
                ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                                sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
                if (ia->buffer.bufferWrite.octets == NULL) {
                    return;
                }
                ia->buffer.bufferWrite.octets = (u_int8_t *)strcat((char *)ia->buffer.bufferWrite.octets, "egg ");
            }
        }
    }
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[0]; j++) {
        ia->buffer.bufferWrite.usedSize += 5;
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        ia->buffer.bufferWrite.octets = (u_int8_t *)strcat((char *)ia->buffer.bufferWrite.octets, "food ");
    }
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[1]; j++) {
        ia->buffer.bufferWrite.usedSize += 9;
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        ia->buffer.bufferWrite.octets = (u_int8_t *)strcat((char *)ia->buffer.bufferWrite.octets, "linemate ");
    }
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[2]; j++) {
        ia->buffer.bufferWrite.usedSize += 10;
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        ia->buffer.bufferWrite.octets = (u_int8_t *)strcat((char *)ia->buffer.bufferWrite.octets, "deraumere ");
    }
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[3]; j++) {
        ia->buffer.bufferWrite.usedSize += 6;
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        ia->buffer.bufferWrite.octets = (u_int8_t *)strcat((char *)ia->buffer.bufferWrite.octets, "sibur ");
    }
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[4]; j++) {
        ia->buffer.bufferWrite.usedSize += 9;
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        ia->buffer.bufferWrite.octets = (u_int8_t *)strcat((char *)ia->buffer.bufferWrite.octets, "mendiane ");
    }
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[5]; j++) {
        ia->buffer.bufferWrite.usedSize += 7;
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        ia->buffer.bufferWrite.octets = (u_int8_t *)strcat((char *)ia->buffer.bufferWrite.octets, "phiras ");
    }
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[6]; j++) {
        ia->buffer.bufferWrite.usedSize += 9;
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        ia->buffer.bufferWrite.octets = (u_int8_t *)strcat((char *)ia->buffer.bufferWrite.octets, "thystame ");
    }
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize] = ',';
}

static void funct_response_look_north(ia_t *ia, common_t *com)
{
    int nbr_tiles = 0;
    int nbr_tiles_left = 0;
    int post_x_start = 0;
    int post_y_start = ia->player->y - 1;

    ia->buffer.bufferWrite.usedSize = 1;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                            sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '[';
    for (size_t level = 0; level < ia->player->level; level++) {
        nbr_tiles = 3 + level * 2;
        nbr_tiles_left = (nbr_tiles - 1) / 2;
        post_x_start = ia->player->x - nbr_tiles_left;
        if (post_x_start < 0) {
            post_x_start = com->gui->map.height + post_x_start;
        }
        if (post_y_start < 0) {
            post_y_start = com->gui->map.width;
        }
        for (int tmp = 0; tmp < nbr_tiles; tmp++) {
            if (post_x_start > (int)com->gui->map.height) {
                post_x_start = 0;
            }
            to_take_ressources_response_ia(ia, com, post_x_start, post_y_start);
            post_x_start += 1;
        }
        post_y_start -= 1;
    }
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize] = '\n';
    ia->buffer.bufferWrite.usedSize += 1;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                            sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize] = '\0';
}

static void funct_response_look_sud(ia_t *ia, common_t *com)
{
    int nbr_tiles = 0;
    int nbr_tiles_left = 0;
    int post_x_start = 0;
    int post_y_start = ia->player->y + 1;

    ia->buffer.bufferWrite.usedSize = 1;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                            sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '[';
    for (size_t level = 0; level < ia->player->level; level++) {
        nbr_tiles = 3 + level * 2;
        nbr_tiles_left = (nbr_tiles - 1) / 2;
        post_x_start = ia->player->x + nbr_tiles_left;
        if (post_x_start > (int)com->gui->map.height) {
            post_x_start -= com->gui->map.height;
        }
        if (post_y_start > (int)com->gui->map.width) {
            post_y_start = 0;
        }
        for (int tmp = 0; tmp < nbr_tiles; tmp++) {
            if (post_x_start < 0) {
                post_x_start = com->gui->map.height;
            }
            to_take_ressources_response_ia(ia, com, post_x_start, post_y_start);
            post_x_start -= 1;
        }
        post_y_start += 1;
    }
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize] = '\n';
    ia->buffer.bufferWrite.usedSize += 1;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                            sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize] = '\0';
}

static void funct_response_look_est(ia_t *ia, common_t *com)
{
    int nbr_tiles = 0;
    int nbr_tiles_left = 0;
    int post_x_start = ia->player->x + 1;
    int post_y_start = 0;

    ia->buffer.bufferWrite.usedSize = 1;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                            sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '[';
    for (size_t level = 0; level < ia->player->level; level++) {
        nbr_tiles = 3 + level * 2;
        nbr_tiles_left = (nbr_tiles - 1) / 2;
        post_y_start = ia->player->y - nbr_tiles_left;
        if (post_x_start > (int)com->gui->map.height) {
            post_x_start = 0;
        }
        if (post_y_start < 0) {
            post_y_start = com->gui->map.width + post_y_start;
        }
        for (int tmp = 0; tmp < nbr_tiles; tmp++) {
            if (post_y_start > (int)com->gui->map.width) {
                post_y_start = 0;
            }
            to_take_ressources_response_ia(ia, com, post_x_start, post_y_start);
            post_y_start += 1;
        }
        post_x_start += 1;
    }
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize] = '\n';
    ia->buffer.bufferWrite.usedSize += 1;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                            sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize] = '\0';
}

static void funct_response_look_west(ia_t *ia, common_t *com)
{
    int nbr_tiles = 0;
    int nbr_tiles_left = 0;
    int post_x_start = ia->player->x - 1;
    int post_y_start = 0;

    ia->buffer.bufferWrite.usedSize = 1;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                            sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '[';
    for (size_t level = 0; level < ia->player->level; level++) {
        nbr_tiles = 3 + level * 2;
        nbr_tiles_left = (nbr_tiles - 1) / 2;
        post_y_start = ia->player->y + nbr_tiles_left;
        if (post_x_start < 0) {
            post_x_start = com->gui->map.height;
        }
        if (post_y_start > (int)com->gui->map.width) {
            post_y_start -= com->gui->map.width;
        }
        for (int tmp = 0; tmp < nbr_tiles; tmp++) {
            if (post_y_start < 0) {
                post_y_start = com->gui->map.width;
            }
            to_take_ressources_response_ia(ia, com, post_x_start, post_y_start);
            post_y_start -= 1;
        }
        post_x_start -= 1;
    }
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize] = '\n';
    ia->buffer.bufferWrite.usedSize += 1;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                            sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize] = '\0';
}

void funct_response_ia_look(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    (void)com;
    if (ia->player->orientation == North) {
        funct_response_look_north(ia, com);
    } else if (ia->player->orientation == Est) {
        funct_response_look_est(ia, com);
    } else if (ia->player->orientation == Sud) {
        funct_response_look_sud(ia, com);
    } else {
        funct_response_look_west(ia, com);
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets,
        ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_look\n");
}
