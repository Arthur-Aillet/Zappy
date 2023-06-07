/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_eject
*/

#include "zappy.h"

void funct_client_ia_eject(ia_t *ia, uint8_t **args)
{
    msg_queue_t new_msg;

    new_msg.time = 7;
    new_msg.handler = &funct_response_ia_eject;
    new_msg.next_msg = ia->msg_queue;
    printf("rentrer dans la funct_client_ia_eject");
    (void)ia;
    (void)args;
    (void)new_msg;
}
