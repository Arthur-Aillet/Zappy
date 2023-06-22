/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_incantation
*/

#include "zappy.h"

static void call_function_gui_bis(ia_t *ia, common_t *com,
                                msg_queue_t *new_msg)
{
    if (ia->player->level == 2 || ia->player->level == 3) {
        status_level_two_tree(ia, com, new_msg);
    } else if (ia->player->level == 4 || ia->player->level == 5) {
        status_level_four_five(ia, com, new_msg);
    } else {
        status_level_other(ia, com, new_msg);
    }
}

static void call_function_gui(ia_t *ia, common_t *com,
                                msg_queue_t *new_msg)
{
    if (to_check_ressources(ia, com,
        ia->player->x, ia->player->y) == -1) {
        to_create_message_response_ia(new_msg);
        return;
    }
    if (ia->player->level == 1) {
        status_level_one(ia, com, new_msg);
    } else {
        call_function_gui_bis(ia, com, new_msg);
    }
}

void funct_client_ia_incantation(ia_t *ia, uint8_t **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    (void)com;
    (void)args;
    if (new_msg == NULL) {
        return;
    }
    if (ia->player->incantation == NO) {
        call_function_gui(ia, com, new_msg);
    } else {
        to_create_message_response_ia(new_msg);
    }
    new_msg->time = 300 / com->freq;
    new_msg->start = 0;
    new_msg->msg = NULL;
    new_msg->handler = &funct_response_ia_incantation;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
    basic_log("rentrer dans la funct_client_ia_incantation", C, 0);
}
