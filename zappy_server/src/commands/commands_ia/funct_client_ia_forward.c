/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_msz
*/

#include "zappy.h"

void funct_client_ia_forward(ia_t *ia, uint8_t **args, common_t *com)
{
    msg_queue_t new_msg;

    (void)com;
    new_msg.time = 7;
    new_msg.handler = &funct_response_ia_forward;
    new_msg.next_msg = ia->msg_queue;
    printf("rentrer dans la funct_client_ia_forward");
    (void)ia;
    (void)args;
    (void)new_msg;
}
