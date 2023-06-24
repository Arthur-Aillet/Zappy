/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_sst
*/

#include "zappy.h"

static void fill_args(msg_queue_t *new_msg, char **args)
{
    new_msg->msg[0] = malloc(sizeof(char) *
                    (strlen(args[0]) + 1));
    if (new_msg->msg[0] == NULL) {
        return;
    }
    new_msg->msg[0][0] = '\0';
    new_msg->msg[0] = strcat(new_msg->msg[0], args[0]);
}

void funct_client_sst(gui_t *gui, char **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    (void)com;
    if (new_msg == NULL) {
        return;
    }
    new_msg->time = 0;
    new_msg->start = 0;
    new_msg->msg = NULL;
    malloc_nbr_args(new_msg, 2);
    fill_args(new_msg, args);
    new_msg->handler = &funct_server_sst;
    new_msg->next_msg = gui->msg_queue;
    gui->msg_queue = new_msg;
}
