/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_remove_player
*/

#include "zappy.h"

/**
 @brief prepare response for the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param int x: the element that must be put in the answer
 for the gui
 @return void
**/
static void funct_prepare_response_gui(player_t *ia, common_t *com, int r)
{
    char **args = malloc(sizeof(char *) * 4);

    if (args == NULL) {
        return;
    }
    args[0] = prepare_arg_response_gui(ia->x);
    args[1] = prepare_arg_response_gui(ia->y);
    args[2] = prepare_arg_response_gui(r);
    args[3] = NULL;
    funct_server_pie(args, com->gui, com);
    free_array((void**)args);
}

/**
 @brief returns the number of elements in the queue
 depending on the commands the AI ​​wants to execute
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia_tmp: structure ia player
 @return int
**/
static int funct_status_master(ia_t *ia_tmp)
{
    int cmp;

    for (cmp = 0; ia_tmp->msg_queue[cmp].next_msg != NULL; cmp++);
    return cmp;
}

/**
 @brief remove the incantation command in the ai which are
 in incantation and change their status
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param player_t *ia: structure ia player
 @param int i: number ia in incantation
 @param char **args: structure ia player
 @return void
**/
static void funct_status_incantation(int i, common_t *com,
                                player_t *ia, char **args)
{
    ia_t *ia_tmp;
    int cmp = 0;

    for (int tmp = 0; tmp < i; tmp++) {
        ia_tmp = to_find_ia_int(com->gui->map.tiles[ia->y][ia->x].
        nb_player_incantations[tmp], com);
        if (ia_tmp->player->incantation == MASTER) {
            cmp = funct_status_master(ia_tmp);
            free_msg_queue(&ia_tmp->msg_queue[cmp]);
            ia_tmp->msg_queue[cmp - 1].next_msg = NULL;
            funct_response_ia_incantation(args, com->gui, com);
        }
        ia_tmp->player->incantation = NO;
    }
}

/**
 @brief check the status incantation and prepare response
 for the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param player_t *ia: structure ia player
 @return void
**/
static void to_check_status_incantation(common_t *com, player_t *ia)
{
    int i = set_nbr_ia(to_find_ia_int(com->gui->map.tiles
    [ia->y][ia->x].nb_player_incantations[0], com));
    char **args = malloc(sizeof(char *) * 2);

    if (args == NULL) {
        return;
    }
    args[0] = malloc(sizeof(char) * 2);
    if (args[0] == NULL) {
        return;
    }
    args[0][0] = '\0';
    args[1] = NULL;
    strcat(args[0], "ko");
    funct_status_incantation(i, com, ia, args);
    funct_prepare_response_gui(ia, com, 0);
    free_array((void**)args);
}

/**
 @brief check if there is an incantation and run and
 if not call the functions to know in which direction the enemy
 should be pushed
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param player_t *ennemy: structure ia ennemy
 @param common_t *common: common structure of all server data
 @param player_t *ia: structure ia player
 @return void
**/
void remove_player(player_t *ennemy, player_t *ia, common_t *com)
{
    if (ennemy->incantation != NO) {
        to_check_status_incantation(com, ia);
    }
    remove_choose_player(ennemy, com, ia);
}
