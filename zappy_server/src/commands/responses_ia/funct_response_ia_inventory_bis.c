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
    ia->buffer.bufferWrite.usedSize = 9 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                        sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    strcat((char*)ia->buffer.bufferWrite.octets, "[food ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
}

void inventory_linemate(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[LINEMATE]);
    ia->buffer.bufferWrite.usedSize += 12 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    strcat((char*)ia->buffer.bufferWrite.octets, "linemate ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
}

void inventory_deraumere(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[DERAUMERE]);
    ia->buffer.bufferWrite.usedSize += 13 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    strcat((char*)ia->buffer.bufferWrite.octets, "deraumere ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
}

void inventory_sibur(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[SIBUR]);
    ia->buffer.bufferWrite.usedSize += 9 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    strcat((char*)ia->buffer.bufferWrite.octets, "sibur ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
}

void inventory_mendiane(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[MENDIANE]);
    ia->buffer.bufferWrite.usedSize += 12 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    strcat((char*)ia->buffer.bufferWrite.octets, "mendiane ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
}
