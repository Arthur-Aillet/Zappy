/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_eject
*/

#include "zappy.h"

void funct_client_ia_eject(ia_t *ia, char **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    (void)com;
    (void)args;
    new_msg->time = 7. / (double)com->freq;
    new_msg->start = 0;
    new_msg->msg = NULL;
    new_msg->handler = &funct_response_ia_eject;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
}
