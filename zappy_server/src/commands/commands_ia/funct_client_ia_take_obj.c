/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_take_obj
*/

#include "zappy.h"

void funct_client_ia_take_obj(ia_t *ia, uint8_t **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    (void)args;
    (void)com;
    if (new_msg == NULL) {
        return;
    }
    new_msg->time = 7;
    new_msg->handler = &funct_response_ia_take_obj;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
    printf("rentrer dans la funct_client_ia_take_obj");
}
