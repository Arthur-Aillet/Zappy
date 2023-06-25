/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** update_msg_queue.c
*/

#include "zappy.h"

static void update_msg_queue(ia_t *ia, common_t *com)
{
    msg_queue_t *msg;
    time_t now = time(NULL);
    if (ia->msg_queue->start == 0) {
        ia->msg_queue->start = now;
        return;
    }
    if (difftime(now, ia->msg_queue->start) >= ia->msg_queue->time) {
        ia->msg_queue->handler(ia->msg_queue->msg, ia, com);
        msg = ia->msg_queue;
        ia->msg_queue = ia->msg_queue->next_msg;
        free(msg);
    }
}

void check_msg_queue_ia(common_t *com)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (com->ia[i].msg_queue != NULL) {
            update_msg_queue(&com->ia[i], com);
        }
    }
}

void check_msg_queue_gui(common_t *com)
{
    msg_queue_t *msg;
    time_t now;
    if (com->gui->msg_queue == NULL)
        return;
    now = time(NULL);
    if (com->gui->msg_queue->start == 0) {
        com->gui->msg_queue->start = now;
        return;
    }
    if (difftime(now, com->gui->msg_queue->start) >=
                com->gui->msg_queue->time) {
        com->gui->msg_queue->handler(com->gui->msg_queue->msg,
                                    (void*)com->gui, com);
        msg = com->gui->msg_queue;
        com->gui->msg_queue = com->gui->msg_queue->next_msg;
        free(msg);
    }
}
