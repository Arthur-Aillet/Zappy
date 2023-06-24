/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_inventory_bis
*/

#include "zappy.h"

void inventory_food(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[FOOD]);
    SIZE = 9 + strlen(buffer_inventory);
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    strcat(OCTETS, "[food ");
    strcat(OCTETS, buffer_inventory);
    strcat(OCTETS, ", ");
}

void inventory_linemate(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[LINEMATE]);
    SIZE += 12 + strlen(buffer_inventory);
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    strcat(OCTETS, "linemate ");
    strcat(OCTETS, buffer_inventory);
    strcat(OCTETS, ", ");
}

void inventory_deraumere(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[DERAUMERE]);
    SIZE += 13 + strlen(buffer_inventory);
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    strcat(OCTETS, "deraumere ");
    strcat(OCTETS, buffer_inventory);
    strcat(OCTETS, ", ");
}

void inventory_sibur(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[SIBUR]);
    SIZE += 9 + strlen(buffer_inventory);
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    strcat(OCTETS, "sibur ");
    strcat(OCTETS, buffer_inventory);
    strcat(OCTETS, ", ");
}

void inventory_mendiane(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[MENDIANE]);
    SIZE += 12 + strlen(buffer_inventory);
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    strcat(OCTETS, "mendiane ");
    strcat(OCTETS, buffer_inventory);
    strcat(OCTETS, ", ");
}
