/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_sgt
*/

#include "zappy.h"
#include <string.h>

/**
 @brief fill in the arguments in the char **msg in the
        new command save to queue
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param msg_queue_t *new_msg: structure of ia
 @param char **args: the arguments given as parameters with the
                command sent by the ia
 @return void
**/
static void fill_args(msg_queue_t *new_msg, char **args)
{
    new_msg->msg[0] = malloc(sizeof(char) *
                    (strlen(args[0]) + 1));
    if (new_msg->msg[0] == NULL) {
        return;
    }
    new_msg->msg[0][0] = '\0';
    new_msg->msg[0] = strcat(new_msg->msg[0],
                    args[0]);
    new_msg->msg[1] = malloc(sizeof(char) *
                    (strlen(args[1]) + 1));
    if (new_msg->msg[0] == NULL) {
        return;
    }
    new_msg->msg[1][0] = '\0';
    new_msg->msg[1] = strcat(new_msg->msg[0], args[1]);
}

/**
 @brief receive and prepare the elements needed to prepare the order
        that will be processed by the server for the command msg
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure of ia
 @param char **args: the arguments receive with the command ia
 @param common_t com: structure commun -> this structure gathers
                all the server data
 @return void
**/
void funct_client_ia_msg(ia_t *ia, char **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    (void)args;
    (void)com;
    if (new_msg == NULL) {
        return;
    }
    new_msg->time = 0;
    new_msg->start = 0;
    new_msg->msg = NULL;
    malloc_nbr_args(new_msg, 2);
    fill_args(new_msg, args);
    new_msg->handler = &funct_response_ia_msg;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
}
