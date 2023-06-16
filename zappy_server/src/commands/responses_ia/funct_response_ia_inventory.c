/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_inventory
*/

#include "zappy.h"

void inventory_food(ia_t *ia)
{
    char buffer_inventory[256];
    strcat((char*)ia->buffer.bufferWrite.octets, "[food ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventory, "%ld", ia->player->inventory[1]);
    ia->buffer.bufferWrite.usedSize += 11 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
}

void inventory_linemate(ia_t *ia)
{
    char buffer_inventory[256];
     strcat((char*)ia->buffer.bufferWrite.octets, "linemate ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventory, "%ld", ia->player->inventory[2]);
    ia->buffer.bufferWrite.usedSize += 12 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
}

void inventory_deraumere(ia_t *ia)
{
    char buffer_inventory[256];
    strcat((char*)ia->buffer.bufferWrite.octets, "deraumere ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventory, "%ld", ia->player->inventory[3]);
    ia->buffer.bufferWrite.usedSize += 8 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
}

void inventory_sibur(ia_t *ia)
{
    char buffer_inventory[256];
    strcat((char*)ia->buffer.bufferWrite.octets, "sibur ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventory, "%ld", ia->player->inventory[4]);
    ia->buffer.bufferWrite.usedSize += 11 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
}

void inventory_mendiane(ia_t *ia)
{
    char buffer_inventory[256];
    strcat((char*)ia->buffer.bufferWrite.octets, "mendiane ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventory, "%ld", ia->player->inventory[5]);
    ia->buffer.bufferWrite.usedSize += 9 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
}

void inventory_phiras(ia_t *ia)
{
    char buffer_inventory[256];
    strcat((char*)ia->buffer.bufferWrite.octets, "phiras ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventory, "%ld", ia->player->inventory[6]);
    ia->buffer.bufferWrite.usedSize += 11 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
}

void inventory_thystame(ia_t *ia)
{
    char buffer_inventory[256];
    strcat((char*)ia->buffer.bufferWrite.octets, "thystame ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventory, "%ld", ia->player->inventory[7]);
    ia->buffer.bufferWrite.usedSize += 7 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
}

void inventory_egg(ia_t *ia)
{
    char buffer_inventory[256];
    strcat((char*)ia->buffer.bufferWrite.octets, "egg ");
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_inventory);
    strcat((char*)ia->buffer.bufferWrite.octets, "]\n\0");
}

void funct_response_ia_inventory(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    char buffer_inventory[256];

    (void)args;
    (void)com;
    sprintf(buffer_inventory, "%ld", ia->player->inventory[0]);
    ia->buffer.bufferWrite.usedSize = 8 + strlen(buffer_inventory);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '\0';
    inventory_food(ia);
    inventory_linemate(ia);
    inventory_deraumere(ia);
    inventory_sibur(ia);
    inventory_mendiane(ia);
    inventory_phiras(ia);
    inventory_thystame(ia);
    inventory_egg(ia);
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets, ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_inventory\n");
}
