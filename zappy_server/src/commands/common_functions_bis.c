/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** common_functions_bis
*/

#include "zappy.h"

void free_arg(int nbr, char **arg)
{
    for (int i = 0; i < nbr; i++) {
        free(arg[i]);
    }
    free(arg);
}

// void free_msg_queue(msg_queue_t msg)
// {
//     for (int i = 0; msg.msg[i]; i++) {
//         free(msg.msg[i]);
//     }
//     free(msg.msg);
// }
