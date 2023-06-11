/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_inventory
*/

#include "zappy.h"

void funct_response_ia_inventory(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    char buffer_inventaire[256];

    (void)args;
    (void)com;
    sprintf(buffer_inventaire, "%ld", ia->player->inventory[0]);
    ia->buffer.bufferWrite.usedSize = 8 + strlen(buffer_inventaire);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat(ia->buffer.bufferWrite.octets, "[food ");
    strcat(ia->buffer.bufferWrite.octets, buffer_inventaire);
    strcat(ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventaire, "%ld", ia->player->inventory[1]);
    ia->buffer.bufferWrite.usedSize += 11 + strlen(buffer_inventaire);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    strcat(ia->buffer.bufferWrite.octets, "linemate ");
    strcat(ia->buffer.bufferWrite.octets, buffer_inventaire);
    strcat(ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventaire, "%ld", ia->player->inventory[2]);
    ia->buffer.bufferWrite.usedSize += 12 + strlen(buffer_inventaire);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    strcat(ia->buffer.bufferWrite.octets, "deraumere ");
    strcat(ia->buffer.bufferWrite.octets, buffer_inventaire);
    strcat(ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventaire, "%ld", ia->player->inventory[3]);
    ia->buffer.bufferWrite.usedSize += 8 + strlen(buffer_inventaire);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    strcat(ia->buffer.bufferWrite.octets, "sibur ");
    strcat(ia->buffer.bufferWrite.octets, buffer_inventaire);
    strcat(ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventaire, "%ld", ia->player->inventory[4]);
    ia->buffer.bufferWrite.usedSize += 11 + strlen(buffer_inventaire);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    strcat(ia->buffer.bufferWrite.octets, "mendiane ");
    strcat(ia->buffer.bufferWrite.octets, buffer_inventaire);
    strcat(ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventaire, "%ld", ia->player->inventory[5]);
    ia->buffer.bufferWrite.usedSize += 9 + strlen(buffer_inventaire);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    strcat(ia->buffer.bufferWrite.octets, "phiras ");
    strcat(ia->buffer.bufferWrite.octets, buffer_inventaire);
    strcat(ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventaire, "%ld", ia->player->inventory[6]);
    ia->buffer.bufferWrite.usedSize += 11 + strlen(buffer_inventaire);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    strcat(ia->buffer.bufferWrite.octets, "thystame ");
    strcat(ia->buffer.bufferWrite.octets, buffer_inventaire);
    strcat(ia->buffer.bufferWrite.octets, ", ");
    sprintf(buffer_inventaire, "%ld", ia->player->inventory[7]);
    ia->buffer.bufferWrite.usedSize += 7 + strlen(buffer_inventaire);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    strcat(ia->buffer.bufferWrite.octets, "egg ");
    strcat(ia->buffer.bufferWrite.octets, buffer_inventaire);
    strcat(ia->buffer.bufferWrite.octets, "]\n\0");
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets, ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_inventory\n");
}
