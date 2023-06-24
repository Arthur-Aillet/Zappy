/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_inventory
*/

#include "zappy.h"

static void inventory_phiras(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[PHIRAS]);
    ia->buffer.bufferWrite.usedSize += 10 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(char) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    strcat(ia->buffer.bufferWrite.octets, "phiras ");
    strcat(ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat(ia->buffer.bufferWrite.octets, ", ");
}

static void inventory_thystame(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[THYSTAME]);
    ia->buffer.bufferWrite.usedSize += 12 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(char) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    strcat(ia->buffer.bufferWrite.octets, "thystame ");
    strcat(ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat(ia->buffer.bufferWrite.octets, ", ");
}

static void inventory_egg(ia_t *ia)
{
    char buffer_inventory[256];

    sprintf(buffer_inventory, "%ld", ia->player->inventory[EGG]);
    ia->buffer.bufferWrite.usedSize += 7 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(char) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    strcat(ia->buffer.bufferWrite.octets, "egg ");
    strcat(ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat(ia->buffer.bufferWrite.octets, "]\n\0");
    ia->buffer.bufferWrite.usedSize =
    strlen(ia->buffer.bufferWrite.octets);
}

static void funct_result_response_ia_inventory(ia_t *ia)
{
    ia->buffer.bufferWrite.octets = malloc(sizeof(char));
    ia->buffer.bufferWrite.octets[0] = '\0';
    inventory_food(ia);
    inventory_linemate(ia);
    inventory_deraumere(ia);
    inventory_sibur(ia);
    inventory_mendiane(ia);
    inventory_phiras(ia);
    inventory_thystame(ia);
    inventory_egg(ia);
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets,
        ia->buffer.bufferWrite.usedSize);
}

void funct_response_ia_inventory(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    (void)args;
    (void)com;
    funct_result_response_ia_inventory(ia);
    basic_log("Check his inventory", C, 0);
}
