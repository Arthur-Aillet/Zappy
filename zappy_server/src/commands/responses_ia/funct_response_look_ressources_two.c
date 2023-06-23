/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_look_ressources_two
*/

#include "zappy.h"

static void to_take_ressources_response_ia_linemate(ia_t *ia,
                                        common_t *com, int x, int y)
{
    for (size_t j = 0; j < com->gui->map.tiles[y][x].ressources[LINEMATE]; j++) {
        ia->buffer.bufferWrite.usedSize += 9;
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char *)ia->buffer.bufferWrite.octets, "linemate ");
    }
    to_take_ressources_response_ia_deraumere(ia, com, x, y);
}

void to_take_ressources_response_ia_food(ia_t *ia,
                                    common_t *com, int x, int y)
{
    for (size_t j = 0; j < com->gui->map.tiles[y][x].ressources[FOOD]; j++) {
        ia->buffer.bufferWrite.usedSize += 5;
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * ia->buffer.bufferWrite.usedSize);
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char *)ia->buffer.bufferWrite.octets, "food ");
    }
    to_take_ressources_response_ia_linemate(ia, com, x, y);
}
