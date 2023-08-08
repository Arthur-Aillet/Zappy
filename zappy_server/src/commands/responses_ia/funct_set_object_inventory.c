/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_set_object_inventory
*/

#include "zappy.h"

/**
 @brief prepare response for the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: the ia structure
 @param int idx: resource number
 @param char **args: the arguments you need to answer the gui
 @return char *
**/
static void funct_response_gui(ia_t *ia, int idx, common_t *com, char **args)
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
    funct_server_pdr(args, com->gui, com);
}

/**
 @brief set command response to ia
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: the ia structure
 @param int idx: resource number
 @return void
**/
void response_set(ia_t *ia, int idx, common_t *com)
{
    char **args = malloc(sizeof(char *) * 3);

    if (args == NULL) {
        return;
    }
    if (ia->player->inventory[idx] > 0) {
        ia->player->inventory[idx] -= 1;
        update_density(&C_DENSITY[idx],
        &C_RESSOURCES(ia->player->y, ia->player->x)[idx], 1);
        funct_response_gui(ia, idx, com, args);
        strcat(OCTETS, "ok\n\0");
        update_tile_gui(com, ia);
    } else
        strcat(OCTETS, "ko\n\0");
    free_array((void **)args);
}

/**
 @brief find the resource that needs to be modified tree part
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: the ia structure
 @param char **args: the arguments you need to answer the gui
 @return char *
**/
static void next_if_funct_tree(ia_t *ia, common_t *com, char **args)
{
    if (strcmp(args[0], "phiras") == 0) {
        response_set(ia, 5, com);
    } else if (strcmp(args[0], "thystame") == 0) {
        response_set(ia, 6, com);
    } else {
        strcat(OCTETS, "ko\n\0");
    }
}

/**
 @brief find the resource that needs to be modified second part
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: the ia structure
 @param char **args: the arguments you need to answer the gui
 @return char *
**/
static void next_if_funct_bis(ia_t *ia, common_t *com, char **args)
{
    if (strcmp(args[0], "sibur") == 0) {
        response_set(ia, 3, com);
    } else if (strcmp(args[0], "mendiane") == 0) {
        response_set(ia, 4, com);
    } else {
        next_if_funct_tree(ia, com, args);
    }
}

/**
 @brief find the resource that needs to be modified first part
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: the ia structure
 @param char **args: the arguments you need to answer the gui
 @return char *
**/
void next_if_funct_set(ia_t *ia, common_t *com, char **args)
{
    if (strcmp(args[0], "linemate") == 0) {
        response_set(ia, 1, com);
    } else if (strcmp(args[0], "deraumere") == 0) {
        response_set(ia, 2, com);
    } else {
        next_if_funct_bis(ia, com, args);
    }
}
