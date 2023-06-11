/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_set_obj
*/

#include "zappy.h"

void funct_response_ia_set_obj(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    (void)com;
    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    ia->buffer.bufferWrite.octets[0] = '\0';
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    } else if (strcmp(args[0], "FOOD")) {
        if (ia->player->inventory[0] > 0) {
            ia->player->inventory[0] -= 1;
            strcat(ia->buffer.bufferWrite.octets, "ok\n\0");
        }
        strcat(ia->buffer.bufferWrite.octets, "ko\n\0");
    } else if (strcmp(args[0], "LINEMATE")) {
        if (ia->player->inventory[1] > 0) {
            ia->player->inventory[1] -= 1;
            strcat(ia->buffer.bufferWrite.octets, "ok\n\0");
        }
        strcat(ia->buffer.bufferWrite.octets, "ko\n\0");
    } else if (strcmp(args[0], "DERAUMERE")) {
        if (ia->player->inventory[2] > 0) {
            ia->player->inventory[2] -= 1;
            strcat(ia->buffer.bufferWrite.octets, "ok\n\0");
        }
        strcat(ia->buffer.bufferWrite.octets, "ko\n\0");
    } else if (strcmp(args[0], "SIBUR")) {
        if (ia->player->inventory[3] > 0) {
            ia->player->inventory[3] -= 1;
            strcat(ia->buffer.bufferWrite.octets, "ok\n\0");
        }
        strcat(ia->buffer.bufferWrite.octets, "ko\n\0");
    } else if (strcmp(args[0], "MENDIANE")) {
        if (ia->player->inventory[4] > 0) {
            ia->player->inventory[4] -= 1;
            strcat(ia->buffer.bufferWrite.octets, "ok\n\0");
        }
        strcat(ia->buffer.bufferWrite.octets, "ko\n\0");
    } else if (strcmp(args[0], "PHIRAS")) {
        if (ia->player->inventory[5] > 0) {
            ia->player->inventory[5] -= 1;
            strcat(ia->buffer.bufferWrite.octets, "ok\n\0");
        }
        strcat(ia->buffer.bufferWrite.octets, "ko\n\0");
    } else if (strcmp(args[0], "THYSTAME")) {
        if (ia->player->inventory[6] > 0) {
            ia->player->inventory[6] -= 1;
            strcat(ia->buffer.bufferWrite.octets, "ok\n\0");
        }
        strcat(ia->buffer.bufferWrite.octets, "ko\n\0");
    } else if (strcmp(args[0], "THYSTAME")) {
        if (ia->player->inventory[7] > 0) {
            ia->player->inventory[7] -= 1;
            strcat(ia->buffer.bufferWrite.octets, "ok\n\0");
        }
        strcat(ia->buffer.bufferWrite.octets, "ko\n\0");
    } else {
        strcat(ia->buffer.bufferWrite.octets, "ko\n\0");
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets, ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_set_obj\n");
}
