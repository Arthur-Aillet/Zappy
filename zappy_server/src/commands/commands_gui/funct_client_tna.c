/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_tna
*/

#include "zappy.h"

void funct_client_tna(gui_t *gui, uint8_t **args, common_t *com)
{
    (void)args;
    (void)com;
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    if (new_msg == NULL) {
        //error
        return;
    }
    new_msg->time = 0;
    new_msg->handler = &funct_server_tna;
    new_msg->next_msg = gui->msg_queue;
    gui->msg_queue = new_msg;
    printf("rentrer dans la funct_client_tna\n");
}
