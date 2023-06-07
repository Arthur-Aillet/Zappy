/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_sst
*/

#include "zappy.h"

void funct_client_ia_connect_nbr(ia_t *ia, uint8_t **args)
{
    msg_queue_t new_msg;

    new_msg.time = 0;
    new_msg.handler = &funct_response_ia_connect_nbr;
    new_msg.next_msg = ia->msg_queue;
    printf("rentrer dans la funct_client_ia_connect_nbr");
    (void)ia;
    (void)args;
    (void)new_msg;
}
