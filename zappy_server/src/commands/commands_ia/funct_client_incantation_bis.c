/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_incantation_bis
*/

#include "zappy.h"

static void status_level_four_five_bis(ia_t *ia,
            common_t *com, msg_queue_t *new_msg, u_int8_t **arg)
{
    int result_ia = 0;

    for (int i = 0; i < 3; i++) {
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[4 + i] = create_new_arg(result_ia, new_msg);
    }
    to_complete_ia_in_incantation(4, arg,
    &com->gui->map.tiles[ia->player->y][ia->player->x]);
    funct_server_pic(arg, com->gui, com);
    free_arg(7, arg);
}

void status_level_four_five(ia_t *ia, common_t *com, msg_queue_t *new_msg)
{
    u_int8_t **arg = malloc(sizeof(u_int8_t *) * 7);

    if (arg == NULL) {
        to_create_message_response_ia(new_msg);
        return;
    }
    arg[0] = create_new_arg(ia->player->x, new_msg);
    arg[1] = create_new_arg(ia->player->y, new_msg);
    arg[2] = create_new_arg(ia->player->level, new_msg);
    arg[3] = create_new_arg(ia->player->id, new_msg);
    status_level_four_five_bis(ia, com, new_msg, arg);
}

static void status_level_other_bis(ia_t *ia,
            common_t *com, msg_queue_t *new_msg, u_int8_t **arg)
{
    int result_ia = 0;

    for (int i = 0; i < 5; i++) {
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[4 + i] = create_new_arg(result_ia, new_msg);
    }
    to_complete_ia_in_incantation(6, arg,
    &com->gui->map.tiles[ia->player->y][ia->player->x]);
    funct_server_pic(arg, com->gui, com);
    free_arg(9, arg);
}

void status_level_other(ia_t *ia, common_t *com, msg_queue_t *new_msg)
{
    u_int8_t **arg = malloc(sizeof(u_int8_t *) * 7);

    if (arg == NULL) {
        to_create_message_response_ia(new_msg);
        return;
    }
    arg[0] = create_new_arg(ia->player->x, new_msg);
    arg[1] = create_new_arg(ia->player->y, new_msg);
    arg[2] = create_new_arg(ia->player->level, new_msg);
    arg[3] = create_new_arg(ia->player->id, new_msg);
    status_level_other_bis(ia, com, new_msg, arg);
}
