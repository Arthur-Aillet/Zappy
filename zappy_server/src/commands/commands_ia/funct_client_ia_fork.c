/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_fork
*/

#include "zappy.h"

static void call_function_gui(ia_t *ia, common_t *com)
{
    uint8_t **arg = malloc(sizeof(uint8_t *) * 1);
    char buffer_player[256];

    if (arg == NULL) {
        return;
    }
    sprintf(buffer_player, "%d", ia->player->id);
    arg[0] = malloc(sizeof(uint8_t) * (strlen(buffer_player) + 1));
    if (arg[0] == NULL) {
    }
    arg[0][0] = '\0';
    strcat((char*)arg[0], buffer_player);
    funct_server_pfk(arg, com->gui, com);
    free_arg(1, arg);
}

void funct_client_ia_fork(ia_t *ia, uint8_t **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    (void)args;
    if (new_msg == NULL) {
        return;
    }
    call_function_gui(ia, com);
    new_msg->time = 42 / com->freq;
    new_msg->start = 0;
    new_msg->msg = NULL;
    new_msg->handler = &funct_response_ia_fork;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
    basic_log("rentrer dans la funct_client_ia_fork", C, 0);
}
