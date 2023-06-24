/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_take_object_inventory
*/

#include "zappy.h"

static void funct_response_gui(ia_t *ia, int idx,
                        common_t *com, char **args)
{
    char buffer_args[256];

    sprintf(buffer_args, "%d", ia->player->id);
    args[0] = malloc(sizeof(char) * (strlen(buffer_args) + 1));
    if (args[0] == NULL) {
        return;
    }
    args[0][0] = '\0';
    strcat(args[0], buffer_args);
    sprintf(buffer_args, "%d", idx);
    args[1] = malloc(sizeof(char) * (strlen(buffer_args) + 1));
    if (args[1] == NULL) {
        return;
    }
    args[1][0] = '\0';
    strcat(args[1], buffer_args);
    args[2] = NULL;
    funct_server_pgt(args, com->gui, com);
}

void response_take(ia_t *ia, int idx, common_t *com)
{
    char **args = malloc(sizeof(char *) * 3);

    if (args == NULL) {
        return;
    }
    if (com->gui->map.tiles[ia->player->y][ia->player->x].ressources[idx]
                                                                        > 0) {
        ia->player->inventory[idx] += 1;
        update_density(&C_DENSITY[idx], &com->gui->map.tiles[ia->player->y][ia->player->x].ressources[idx], -1);
        funct_response_gui(ia, idx, com, args);
        update_tile_gui(com, ia);
        strcat(OCTETS, "ok\n\0");
    } else
        strcat(OCTETS, "ko\n\0");
    free_array((void **)args);
}

static void next_if_funct_tree(ia_t *ia, common_t *com, char **args)
{
    if (strcmp(args[0], "phiras") == 0) {
        response_take(ia, 5, com);
    } else if (strcmp(args[0], "thystame") == 0) {
        response_take(ia, 6, com);
    } else {
        strcat(OCTETS, "ko\n\0");
    }
}

static void next_if_funct_bis(ia_t *ia, common_t *com, char **args)
{
    if (strcmp(args[0], "sibur") == 0) {
        response_take(ia, 3, com);
    } else if (strcmp(args[0], "mendiane") == 0) {
        response_take(ia, 4, com);
    } else {
        next_if_funct_tree(ia, com, args);
    }
}

void next_if_funct_take(ia_t *ia, common_t *com, char **args)
{
    if (strcmp(args[0], "linemate") == 0) {
        response_take(ia, 1, com);
    } else if (strcmp(args[0], "deraumere") == 0) {
        response_take(ia, 2, com);
    } else {
        next_if_funct_bis(ia, com, args);
    }
}
