/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_incantation
*/

#include "zappy.h"

//voir fonction après

void funct_client_ia_incantation(ia_t *ia, uint8_t **args)
{
    msg_queue_t new_msg;

    new_msg.time = 300;
    new_msg.handler = &funct_response_ia_incantation;
    new_msg.next_msg = ia->msg_queue;
    printf("rentrer dans la funct_client_ia_incantation");
}
