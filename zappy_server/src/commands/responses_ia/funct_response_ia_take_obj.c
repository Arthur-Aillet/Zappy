/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_take_obj
*/

#include "zappy.h"

static void response(ia_t *ia, common_t *com, int idx)
{
    u_int8_t **args = malloc(sizeof(u_int8_t *) * 2);
    char buffer_args[256];

    if (args == NULL) {
        //error
    }
    if (com->gui->map.tiles[ia->player->x][ia->player->y].ressources[idx] > 0) {
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[idx] -= 1;
        ia->player->inventory[idx] += 1;
        sprintf(buffer_args, "%d", ia->player->id);
        args[0] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
        if (args[0] == NULL) {
            //error
        }
        args[0][0] = '\0';
        strcat((char*)args[0], buffer_args);
        sprintf(buffer_args, "%d", idx);
        args[1] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
        if (args[1] == NULL) {
            //error
        }
        args[1][0] = '\0';
        strcat((char*)args[1], buffer_args);
        funct_server_pgt(args, com->gui, com);
        strcat((char*)ia->buffer.bufferWrite.octets, "ok\n\0");
    }
    strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
}

void funct_response_ia_take_obj(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    ia->buffer.bufferWrite.octets[0] = '\0';
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    } else if (strcmp((char*)args[0], "FOOD")) {
        response(ia, com, 0);
    } else if (strcmp((char*)args[0], "LINEMATE")) {
        response(ia, com, 1);
    } else if (strcmp((char*)args[0], "DERAUMERE")) {
        response(ia, com, 2);
    } else if (strcmp((char*)args[0], "SIBUR")) {
        response(ia, com, 3);
    } else if (strcmp((char*)args[0], "MENDIANE")) {
        response(ia, com, 4);
    } else if (strcmp((char*)args[0], "PHIRAS")) {
        response(ia, com, 5);
    } else if (strcmp((char*)args[0], "THYSTAME")) {
        response(ia, com, 6);
    } else {
        strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets, ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_take_obj\n");
}
