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
    for (size_t j = 0; j < C_RESSOURCES(y, x)[LINEMATE]; j++) {
        SIZE += 9;
        OCTETS = realloc(OCTETS, sizeof(char) * SIZE);
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "linemate ");
    }
    to_take_ressources_response_ia_deraumere(ia, com, x, y);
}

void to_take_ressources_response_ia_food(ia_t *ia, common_t *com, int x, int y)
{
    printf("x: %d y: %d\n", x, y);
    if (OCTETS == NULL)
        OCTETS = malloc(sizeof(char));
    for (size_t j = 0; j < C_RESSOURCES(y, x)[FOOD]; j++) {
        SIZE += 5;
        OCTETS = realloc(OCTETS, sizeof(char) * (SIZE + 1));
        if (OCTETS == NULL) {
            return;
        }
        strcat(OCTETS, "food ");
    }
    to_take_ressources_response_ia_linemate(ia, com, x, y);
}
