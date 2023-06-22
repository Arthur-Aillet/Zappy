/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_ppo
*/

#include "zappy.h"
#include <string.h>

static void fill_args(msg_queue_t *new_msg, uint8_t **args, int idx)
{
    new_msg->msg[idx] = malloc(sizeof(uint8_t) * (strlen((char*)args[idx]) + 1));
    if (new_msg->msg[idx] == NULL) {
        return;
    }
    new_msg->msg[idx][0] = '\0';
    new_msg->msg[idx] = (uint8_t*)strcat((char*)new_msg->msg[idx], (char*)args[idx]);
}

void funct_client_ia_broadcast(ia_t *ia, uint8_t **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    if (new_msg == NULL) {
        return;
    }
    size_t array_size;
    for (array_size = 0; args[array_size] != NULL; array_size++);
    new_msg->time = 7 / com->freq;
    new_msg->start = 0;
    malloc_nbr_args(new_msg, array_size + 1);
    for (size_t i = 0; i < array_size; i++) {
        fill_args(new_msg, args, i);
    }
    new_msg->msg[array_size] = NULL;
    new_msg->handler = &funct_response_ia_broadcast;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
    basic_log("rentrer dans la funct_client_ia_broadcast", CYAN, 0);
}
