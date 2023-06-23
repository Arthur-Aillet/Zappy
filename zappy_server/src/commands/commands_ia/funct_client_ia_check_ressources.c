/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_check_ressources
*/

#include "zappy.h"

static int to_check_ressources_six(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 7) {
        if (com->gui->map.tiles[y][x].ressources[1] > 1 &&
        com->gui->map.tiles[y][x].ressources[2] > 1 &&
        com->gui->map.tiles[y][x].ressources[3] > 1 &&
        com->gui->map.tiles[y][x].ressources[4] > 1 &&
        com->gui->map.tiles[y][x].ressources[5] > 1 &&
        com->gui->map.tiles[y][x].ressources[6] > 0) {
            update_density(&com->gui->map.density[1], &com->gui->map.tiles[y][x].ressources[1], -2);
            update_density(&com->gui->map.density[2], &com->gui->map.tiles[y][x].ressources[2], -2);
            update_density(&com->gui->map.density[3], &com->gui->map.tiles[y][x].ressources[3], -2);
            update_density(&com->gui->map.density[4], &com->gui->map.tiles[y][x].ressources[4], -2);
            update_density(&com->gui->map.density[5], &com->gui->map.tiles[y][x].ressources[5], -2);
            update_density(&com->gui->map.density[6], &com->gui->map.tiles[y][x].ressources[6], -1);
            return 0;
        }
    }
    return -1;
}

static int to_check_ressources_five(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 6) {
        if (com->gui->map.tiles[y][x].ressources[1] > 0 &&
        com->gui->map.tiles[y][x].ressources[2] > 1 &&
        com->gui->map.tiles[y][x].ressources[3] > 2 &&
        com->gui->map.tiles[y][x].ressources[5] > 0) {
            update_density(&com->gui->map.density[1], &com->gui->map.tiles[y][x].ressources[1], -1);
            update_density(&com->gui->map.density[2], &com->gui->map.tiles[y][x].ressources[2], -2);
            update_density(&com->gui->map.density[3], &com->gui->map.tiles[y][x].ressources[3], -3);
            update_density(&com->gui->map.density[5], &com->gui->map.tiles[y][x].ressources[5], -1);
            return 0;
        }
    }
    return to_check_ressources_six(ia, com, x, y);
}

static int to_check_ressources_four(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 5) {
        if (com->gui->map.tiles[y][x].ressources[1] > 0 &&
        com->gui->map.tiles[y][x].ressources[2] > 1 &&
        com->gui->map.tiles[y][x].ressources[3] > 0 &&
        com->gui->map.tiles[y][x].ressources[4] > 2) {
            update_density(&com->gui->map.density[1], &com->gui->map.tiles[y][x].ressources[1], -1);
            update_density(&com->gui->map.density[2], &com->gui->map.tiles[y][x].ressources[2], -2);
            update_density(&com->gui->map.density[3], &com->gui->map.tiles[y][x].ressources[3], -1);
            update_density(&com->gui->map.density[4], &com->gui->map.tiles[y][x].ressources[4], -3);
            return 0;
        }
    }
    return to_check_ressources_five(ia, com, x, y);
}

static int to_check_ressources_tree(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 4) {
        if (com->gui->map.tiles[y][x].ressources[1] > 0 &&
        com->gui->map.tiles[y][x].ressources[2] > 0 &&
        com->gui->map.tiles[y][x].ressources[3] > 1 &&
        com->gui->map.tiles[y][x].ressources[5] > 0) {
            update_density(&com->gui->map.density[1], &com->gui->map.tiles[y][x].ressources[1], -1);
            update_density(&com->gui->map.density[2], &com->gui->map.tiles[y][x].ressources[2], -1);
            update_density(&com->gui->map.density[3], &com->gui->map.tiles[y][x].ressources[3], -2);
            update_density(&com->gui->map.density[5], &com->gui->map.tiles[y][x].ressources[5], -1);
            return 0;
        }
    }
    return to_check_ressources_four(ia, com, x, y);
}

int to_check_ressources_bis(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 3) {
        if (com->gui->map.tiles[y][x].ressources[1] > 1 &&
        com->gui->map.tiles[y][x].ressources[3] > 0 &&
        com->gui->map.tiles[y][x].ressources[5] > 1) {
            update_density(&com->gui->map.density[1], &com->gui->map.tiles[y][x].ressources[1], -2);
            update_density(&com->gui->map.density[3], &com->gui->map.tiles[y][x].ressources[3], -1);
            update_density(&com->gui->map.density[5], &com->gui->map.tiles[y][x].ressources[5], -2);
            return 0;
        }
    }
    return to_check_ressources_tree(ia, com, x, y);
}
