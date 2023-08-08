/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_incantation
*/

#include "zappy.h"

/**
 @brief receive and prepare the elements needed to prepare the
        order that will be processed by the server for the command msg
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure of ia
 @param common_t com: structure commun -> this structure gathers
                                                    all the server data
 @param msg_queue_t *new_msg: the arguments given as parameters with the
                                                command sent by the ia
 @return void
**/
static void call_function_gui_bis(ia_t *ia, common_t *com,
                                msg_queue_t *new_msg)
{
    if (ia->player->level == 2 || ia->player->level == 3) {
        status_level_two_tree(ia, com, new_msg);
    } else if (ia->player->level == 4 || ia->player->level == 5) {
        status_level_four_five(ia, com, new_msg);
    } else {
        status_level_other(ia, com, new_msg);
    }
}

/**
 @brief update tile and send the info to the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t com: structure commun -> this structure
                    gathers all the server data
 @param ia_t *ia: structure of ia
 @return void
**/
void update_tile_gui(common_t *com, ia_t *ia)
{
    char **args = malloc(sizeof(char *) * 3);
    char buffer_args[256];

    if (args == NULL)
        return;
    sprintf(buffer_args, "%d", ia->player->x);
    args[0] = malloc(sizeof(char) * (strlen(buffer_args) + 1));
    if (args[0] == NULL)
        return;
    args[0][0] = '\0';
    args[0] = strcat(args[0], buffer_args);
    sprintf(buffer_args, "%d", ia->player->y);
    args[1] = malloc(sizeof(char) * (strlen(buffer_args) + 1));
    if (args[1] == NULL)
        return;
    args[1][0] = '\0';
    args[1] = strcat(args[1], buffer_args);
    args[2] = NULL;
    funct_server_bct(args, com->gui, com);
    free_array((void **)args);
}

/**
 @brief call function on the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure of ia
 @param msg_queue_t *new_msg: the arguments given as
 parameters with the command sent by the ia
 @param common_t com: structure commun -> this structure
 gathers all the server data
 @return void
**/
static void call_function_gui(ia_t *ia, common_t *com, msg_queue_t *new_msg)
{
    if (to_check_ressources(ia, com, ia->player->x, ia->player->y) == -1) {
        return to_create_message_response_ia(new_msg);
    }
    if (ia->player->level == 1) {
        status_level_one(ia, com, new_msg);
    } else {
        call_function_gui_bis(ia, com, new_msg);
    }
    update_tile_gui(com, ia);
}

/**
 @brief receive and prepare the elements needed to prepare
 the order that will be processed by the server for the command incantation
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure of ia
 @param char **args: the arguments receive with the command ia
 @param common_t com: structure commun -> this structure
 gathers all the server data
 @return void
**/
void funct_client_ia_incantation(ia_t *ia, char **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));
    (void)args;
    if (new_msg == NULL) {
        return;
    }
    new_msg->msg = NULL;
    if (ia->player->incantation == NO) {
        call_function_gui(ia, com, new_msg);
    } else {
        to_create_message_response_ia(new_msg);
    }
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
    new_msg->time = 300. / (double)com->freq;
    new_msg->start = 0;
    new_msg->handler = &funct_response_ia_incantation;
}
