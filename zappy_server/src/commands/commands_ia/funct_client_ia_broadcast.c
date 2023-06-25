/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_ppo
*/

#include "zappy.h"
#include <string.h>

/**
 @brief fill in the arguments in the char **msg in the
        new command save to queue
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param msg_queue_t new_msg : recording of the new order in the pending queue
 @param char **args: the arguments given as parameters with
                    the command sent by the gui
 @param int idx : position of the argument that puts in the msg of the
                    structure that will respond to the ai
 @return void
**/
static void fill_args(msg_queue_t *new_msg, char **args, int idx)
{
    new_msg->msg[idx] = malloc(sizeof(char) *
                        (strlen(args[idx]) + 1));
    if (new_msg->msg[idx] == NULL) {
        return;
    }
    new_msg->msg[idx][0] = '\0';
    strcat(new_msg->msg[idx], args[idx]);
}

/**
 @brief receive and prepare the elements needed to prepare the order
            that will be processed by the server for the command bct
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia : structure of ia
 @param char **args: the arguments receive with the command ia
 @param common_t com : structure commun -> this structure
                        gathers all the server data
 @return void
**/
void funct_client_ia_broadcast(ia_t *ia, char **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));
    size_t array_size;

    if (new_msg == NULL) {
        return;
    }
    for (array_size = 0; args[array_size] != NULL; array_size++);
    new_msg->time = 7. / (double)com->freq;
    new_msg->start = 0;
    malloc_nbr_args(new_msg, array_size + 1);
    for (size_t i = 0; i < array_size; i++) {
        fill_args(new_msg, args, i);
    }
    new_msg->msg[array_size] = NULL;
    new_msg->handler = &funct_response_ia_broadcast;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
}
