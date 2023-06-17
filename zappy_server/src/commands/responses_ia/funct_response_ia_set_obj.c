/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_set_obj
*/

#include "zappy.h"

static void response(ia_t *ia, int idx, common_t *com)
{
    u_int8_t **args = malloc(sizeof(u_int8_t *) * 2);
    char buffer_args[256];

    if (args == NULL) {
        //error
    }
    if (ia->player->inventory[idx] > 0) {
        ia->player->inventory[idx] -= 1;
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
        funct_server_pdr(args, com->gui, com);
        strcat((char*)ia->buffer.bufferWrite.octets, "ok\n\0");
    }
    strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
}

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
    } else if (strcmp((char*)args[0], "FOOD")) {
        response(ia, 0, com);
    } else if (strcmp((char*)args[0], "LINEMATE")) {
        response(ia, 1, com);
    } else if (strcmp((char*)args[0], "DERAUMERE")) {
        response(ia, 2, com);
    } else if (strcmp((char*)args[0], "SIBUR")) {
        response(ia, 3, com);
    } else if (strcmp((char*)args[0], "MENDIANE")) {
        response(ia, 4, com);
    } else if (strcmp((char*)args[0], "PHIRAS")) {
        response(ia, 5, com);
    } else if (strcmp((char*)args[0], "THYSTAME")) {
        response(ia, 6, com);
    } else {
        strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets, ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_set_obj\n");
}
