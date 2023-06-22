/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_set_obj
*/

#include "zappy.h"

void funct_client_ia_set_obj(ia_t *ia, uint8_t **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    (void)args;
    (void)com;
    if (new_msg == NULL) {
        return;
    }
    new_msg->msg = malloc(sizeof(uint8_t*) * 2);
    new_msg->msg[0] = malloc(sizeof(uint8_t) * (strlen((char*)args[0]) + 1));
    new_msg->msg[0][0] = '\0';
    new_msg->msg[0] = (uint8_t*)strcat((char*)new_msg->msg[0], (char*)args[0]);
    new_msg->msg[1] = NULL;
    new_msg->time = 7 / com->freq;
    new_msg->start = 0;
    new_msg->handler = &funct_response_ia_set_obj;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
    basic_log("rentrer dans la funct_client_ia_set_obj", C, 0);
}
