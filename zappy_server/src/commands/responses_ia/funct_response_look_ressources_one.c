/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_look_ressources_one
*/

#include "zappy.h"

static void to_take_ressources_response_ia_thystame(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < com->gui->map.tiles[y][x].ressources[6]; j++) {
        SIZE += 9;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "thystame ");
    }
    if (OCTETS[SIZE - 2] != ' ') {
        SIZE += 1;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
    }
    OCTETS[SIZE - 2] = ',';
    OCTETS[SIZE - 1] = '\0';
}

static void to_take_ressources_response_ia_phiras(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < com->gui->map.tiles[y][x].ressources[5]; j++) {
        SIZE += 7;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "phiras ");
    }
    to_take_ressources_response_ia_thystame(ia, com, x, y);
}

static void to_take_ressources_response_ia_mendiane(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < com->gui->map.tiles[y][x].ressources[4]; j++) {
        SIZE += 9;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "mendiane ");
    }
    to_take_ressources_response_ia_phiras(ia, com, x, y);
}

static void to_take_ressources_response_ia_sibur(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < com->gui->map.tiles[y][x].ressources[SIBUR]; j++) {
        SIZE += 6;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "sibur ");
    }
    to_take_ressources_response_ia_mendiane(ia, com, x, y);
}

void to_take_ressources_response_ia_deraumere(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < com->gui->map.tiles[y][x].ressources[2]; j++) {
        SIZE += 10;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "deraumere ");
    }
    to_take_ressources_response_ia_sibur(ia, com, x, y);
}
