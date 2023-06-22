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
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[6]; j++) {
        ia->buffer.bufferWrite.usedSize += 9;
        printf("thystame: usedSize: %ld\n", ia->buffer.bufferWrite.usedSize);
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char *)ia->buffer.bufferWrite.octets, "thystame ");
    }
    ia->buffer.bufferWrite.usedSize += 1;
    printf("vigule: usedSize: %ld\n", ia->buffer.bufferWrite.usedSize);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                    sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize - 3] = ',';
    ia->buffer.bufferWrite.octets[ia->buffer.bufferWrite.usedSize - 2] = ' ';
    printf("usedSize: %ld\n", ia->buffer.bufferWrite.usedSize);
}

static void to_take_ressources_response_ia_phiras(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[5]; j++) {
        ia->buffer.bufferWrite.usedSize += 7;
        printf("phiras: usedSize: %ld\n", ia->buffer.bufferWrite.usedSize);
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char *)ia->buffer.bufferWrite.octets, "phiras ");
    }
    to_take_ressources_response_ia_thystame(ia, com, x, y);
}

static void to_take_ressources_response_ia_mendiane(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[4]; j++) {
        ia->buffer.bufferWrite.usedSize += 9;
        printf("mediane: usedSize: %ld\n", ia->buffer.bufferWrite.usedSize);
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char *)ia->buffer.bufferWrite.octets, "mendiane ");
    }
    to_take_ressources_response_ia_phiras(ia, com, x, y);
}

static void to_take_ressources_response_ia_sibur(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[SIBUR]; j++) {
        ia->buffer.bufferWrite.usedSize += 6;
        printf("sibur: usedSize: %ld\n", ia->buffer.bufferWrite.usedSize);
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char *)ia->buffer.bufferWrite.octets, "sibur ");
    }
    to_take_ressources_response_ia_mendiane(ia, com, x, y);
}

void to_take_ressources_response_ia_deraumere(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < com->gui->map.tiles[x][y].ressources[2]; j++) {
        ia->buffer.bufferWrite.usedSize += 10;
        printf("deraumere: usedSize: %ld\n", ia->buffer.bufferWrite.usedSize);
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char *)ia->buffer.bufferWrite.octets, "deraumere ");
    }
    to_take_ressources_response_ia_sibur(ia, com, x, y);
}
