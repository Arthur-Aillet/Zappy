/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_set_object_inventory
*/

#include "zappy.h"

static void funct_response_gui(ia_t *ia, int idx,
                        common_t *com, uint8_t **args)
{
    char buffer_args[256];

    sprintf(buffer_args, "%d", ia->player->id);
    args[0] = malloc(sizeof(uint8_t) * (strlen(buffer_args) + 1));
    if (args[0] == NULL) {
        return;
    }
    args[0][0] = '\0';
    strcat((char*)args[0], buffer_args);
    sprintf(buffer_args, "%d", idx);
    args[1] = malloc(sizeof(uint8_t) * (strlen(buffer_args) + 1));
    if (args[1] == NULL) {
        return;
    }
    args[1][0] = '\0';
    strcat((char*)args[1], buffer_args);
    funct_server_pdr(args, com->gui, com);
}

void response_set(ia_t *ia, int idx, common_t *com)
{
    uint8_t **args = malloc(sizeof(uint8_t *) * 2);

    if (args == NULL) {
        return;
    }
    if (ia->player->inventory[idx] > 0) {
        ia->player->inventory[idx] -= 1;
        update_density(&com->gui->map.density[idx], &com->gui->map.tiles[ia->player->y][ia->player->x].ressources[idx], 1);
        funct_response_gui(ia, idx, com, args);
        strcat((char*)ia->buffer.bufferWrite.octets, "ok\n\0");
        update_tile_gui(com, ia);
    } else
        strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
}

static void next_if_funct_tree(ia_t *ia, common_t *com, uint8_t **args)
{
    if (strcmp((char*)args[0], "phiras") == 0) {
        response_set(ia, 5, com);
    } else if (strcmp((char*)args[0], "thystame") == 0) {
        response_set(ia, 6, com);
    } else {
        strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
    }
}

static void next_if_funct_bis(ia_t *ia, common_t *com, uint8_t **args)
{
    if (strcmp((char*)args[0], "sibur") == 0) {
        response_set(ia, 3, com);
    } else if (strcmp((char*)args[0], "mendiane") == 0) {
        response_set(ia, 4, com);
    } else {
        next_if_funct_tree(ia, com, args);
    }
}

void next_if_funct_set(ia_t *ia, common_t *com, uint8_t **args)
{
    if (strcmp((char*)args[0], "linemate") == 0) {
        response_set(ia, 1, com);
    } else if (strcmp((char*)args[0], "deraumere") == 0) {
        response_set(ia, 2, com);
    } else {
        next_if_funct_bis(ia, com, args);
    }
}
