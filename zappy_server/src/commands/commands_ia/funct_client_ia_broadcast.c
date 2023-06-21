/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_ppo
*/

#include "zappy.h"
#include <string.h>

static void fill_args(msg_queue_t *new_msg, uint8_t **args)
{
    new_msg->msg[0] = malloc(sizeof(uint8_t) * (strlen((char*)args[0]) + 1));
    if (new_msg->msg[0] == NULL) {
        return;
    }
    new_msg->msg[0][0] = '\0';
    new_msg->msg[0] = (uint8_t*)strcat((char*)new_msg->msg[0], (char*)args[0]);
}

void funct_client_ia_broadcast(ia_t *ia, uint8_t **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    if (new_msg == NULL) {
        return;
    }
    new_msg->time = 7 / com->freq;
    new_msg->start = 0;
    new_msg->msg = NULL;
    malloc_nbr_args(new_msg, 1);
    fill_args(new_msg, args);
    new_msg->handler = &funct_response_ia_broadcast;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
    basic_log("rentrer dans la funct_client_ia_broadcast", CYAN, 0);
}
