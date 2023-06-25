/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_create_check_incantation
*/

#include "zappy.h"

/**
 @brief to find ia for the incantation and create
 new args for the response gui for the level 6 and 7
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param int nbr_ia: nbr d'ia
 @param char **arg: the arguments receive with the command ia
 @param tile_t *tile: each box of the maps
 @return void
**/
void to_complete_ia_in_incantation(int nbr_ia, char **arg, tile_t *tile)
{
    if (nbr_ia == 1) {
        tile->nb_player_incantations =
        realloc(tile->nb_player_incantations, sizeof(size_t) * 1);
        tile->nb_player_incantations[0] = atoi(arg[3]);
    }
    if (nbr_ia == 6) {
        tile->nb_player_incantations =
        realloc(tile->nb_player_incantations, sizeof(size_t) * 6);
        tile->nb_player_incantations[0] = atoi(arg[3]);
        tile->nb_player_incantations[0] = atoi(arg[4]);
        tile->nb_player_incantations[0] = atoi(arg[5]);
        tile->nb_player_incantations[0] = atoi(arg[6]);
        tile->nb_player_incantations[0] = atoi(arg[7]);
        tile->nb_player_incantations[0] = atoi(arg[8]);
    }
    to_complete_ia_in_incantation_bis(nbr_ia, arg, tile);
}

/**
 @brief to find ia for the incantation and create
 new args for the response gui for the level 6 and 7
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param int nbr: nbr d'arguments
 @param msg_queue_t *new_msg: recording of the new
 order in the pending queue
 @return void
**/
char *create_new_arg(int nbr, msg_queue_t *new_msg)
{
    char buffer_player[256];
    char *arg;

    sprintf(buffer_player, "%d", nbr);
    arg = malloc(sizeof(char) * (strlen(buffer_player) + 1));
    if (arg == NULL) {
        to_create_message_response_ia(new_msg);
        return NULL;
    }
    arg[0] = '\0';
    return strcat(arg, buffer_player);
}

/**
 @brief create new args for the level 1
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure of ia
 @param common_t *com: structure commun -> this structure
 gathers all the server data
 @param msg_queue_t *new_msg: recording of the new order
 in the pending queue
 @return void
**/
void status_level_one(ia_t *ia, common_t *com, msg_queue_t *new_msg)
{
    char **arg;

    arg = malloc(sizeof(char *) * 5);
    if (arg == NULL) {
        to_create_message_response_ia(new_msg);
        return;
    }
    arg[0] = create_new_arg(ia->player->x, new_msg);
    arg[1] = create_new_arg(ia->player->y, new_msg);
    arg[2] = create_new_arg(ia->player->level, new_msg);
    arg[3] = create_new_arg(ia->player->id, new_msg);
    arg[4] = NULL;
    to_complete_ia_in_incantation(1, arg,
    &com->gui->map.tiles[ia->player->y][ia->player->x]);
    funct_server_pic(arg, com->gui, com);
    free_array((void **)arg);
}

/**
 @brief to find ia for the incantation and create new
 args for the response gui for the level 2 and 3
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure of ia
 @param common_t *com: structure commun -> this structure
 gathers all the server data
 @param msg_queue_t *new_msg: recording of the new order
 in the pending queue
 @param char **args: the arguments receive with the command ia
 @return void
**/
static void status_level_two_tree_next(ia_t *ia,
            common_t *com, msg_queue_t *new_msg, char **arg)
{
    int result_ia = 0;

    result_ia = to_find_ia_incantation(com, ia);
    if (result_ia == -1) {
        to_create_message_response_ia(new_msg);
        return;
    }
    arg[4] = create_new_arg(result_ia, new_msg);
    to_complete_ia_in_incantation(2, arg,
    &com->gui->map.tiles[ia->player->y][ia->player->x]);
    funct_server_pic(arg, com->gui, com);
    free_arg(5, arg);
}

/**
 @brief create new args for the level 2 and 3
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure of ia
 @param common_t *com: structure commun -> this structure
 gathers all the server data
 @param msg_queue_t *new_msg: recording of the new order in
 the pending queue
 @return void
**/
void status_level_two_tree(ia_t *ia,
                                common_t *com, msg_queue_t *new_msg)
{
    char **arg;

    arg = malloc(sizeof(char *) * 5);
    if (arg == NULL) {
        to_create_message_response_ia(new_msg);
        return;
    }
    arg[0] = create_new_arg(ia->player->x, new_msg);
    arg[1] = create_new_arg(ia->player->y, new_msg);
    arg[2] = create_new_arg(ia->player->level, new_msg);
    arg[3] = create_new_arg(ia->player->id, new_msg);
    status_level_two_tree_next(ia, com, new_msg, arg);
}
