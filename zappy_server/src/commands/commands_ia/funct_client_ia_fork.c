/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_fork
*/

#include "zappy.h"

/**
 @brief call and prepare arguments function gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure of ia
 @param common_t com: structure commun -> this structure
            gathers all the server data
 @return void
**/
static void call_function_gui(ia_t *ia, common_t *com)
{
    char **arg = malloc(sizeof(char *) * 2);
    char buffer_player[256];

    if (arg == NULL) {
        return;
    }
    sprintf(buffer_player, "%d", ia->player->id);
    arg[0] = malloc(sizeof(char) * (strlen(buffer_player) + 1));
    if (arg[0] == NULL) {
        return;
    }
    arg[0][0] = '\0';
    arg[1] = NULL;
    strcat(arg[0], buffer_player);
    funct_server_pfk(arg, com->gui, com);
    free_array((void **)arg);
}

/**
 @brief receive and prepare the elements needed to prepare the order that will
                        be processed by the server for the command fork
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure of ia
 @param char **args: the arguments receive with the command ia
 @param common_t com: structure commun -> this structure gathers
                    all the server data
 @return void
**/
void funct_client_ia_fork(ia_t *ia, char **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    (void)args;
    if (new_msg == NULL) {
        return;
    }
    call_function_gui(ia, com);
    new_msg->time = 42. / (double)com->freq;
    new_msg->start = 0;
    new_msg->msg = NULL;
    new_msg->handler = &funct_response_ia_fork;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
    basic_log("ask for lay an egg", C, 0);
}
