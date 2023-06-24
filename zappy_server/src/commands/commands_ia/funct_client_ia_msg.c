/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_sgt
*/

#include "zappy.h"
#include <string.h>

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
