/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** common_functions
*/

#include "zappy.h"

void malloc_nbr_args(msg_queue_t *new_msg, size_t nbr_args)
{
    new_msg->msg = malloc(sizeof(u_int8_t *) * nbr_args);
    if (new_msg->msg == NULL) {
        //error
    }
}