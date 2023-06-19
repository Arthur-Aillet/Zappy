/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_take_object_inventory
*/

#include "zappy.h"

static void funct_response_gui(ia_t *ia, int idx,
                        common_t *com, u_int8_t **args)
{
    char buffer_args[256];

    sprintf(buffer_args, "%d", ia->player->id);
    args[0] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (args[0] == NULL) {
        return;
    }
    args[0][0] = '\0';
    strcat((char*)args[0], buffer_args);
    sprintf(buffer_args, "%d", idx);
    args[1] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (args[1] == NULL) {
        return;
    }
    args[1][0] = '\0';
    strcat((char*)args[1], buffer_args);
    funct_server_pdr(args, com->gui, com);
}

void response_take(ia_t *ia, int idx, common_t *com)
{
    u_int8_t **args = malloc(sizeof(u_int8_t *) * 2);

    if (args == NULL) {
        return;
    }
    if (ia->player->inventory[idx] > 0) {
        ia->player->inventory[idx] += 1;
        funct_response_gui(ia, idx, com, args);
        strcat((char*)ia->buffer.bufferWrite.octets, "ok\n\0");
    }
    strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
}

static void next_if_funct_tree(ia_t *ia, common_t *com, uint8_t **args)
{
    if (strcmp((char*)args[0], "PHIRAS")) {
        response_take(ia, 5, com);
    } else if (strcmp((char*)args[0], "THYSTAME")) {
        response_take(ia, 6, com);
    } else {
        strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
    }
}

static void next_if_funct_bis(ia_t *ia, common_t *com, uint8_t **args)
{
    if (strcmp((char*)args[0], "SIBUR")) {
        response_take(ia, 3, com);
    } else if (strcmp((char*)args[0], "MENDIANE")) {
        response_take(ia, 4, com);
    } else {
        next_if_funct_tree(ia, com, args);
    }
}

void next_if_funct_take(ia_t *ia, common_t *com, uint8_t **args)
{
    if (strcmp((char*)args[0], "LINEMATE")) {
        response_take(ia, 1, com);
    } else if (strcmp((char*)args[0], "DERAUMERE")) {
        response_take(ia, 2, com);
    } else {
        next_if_funct_bis(ia, com, args);
    }
}
