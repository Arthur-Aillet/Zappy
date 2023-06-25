/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** update_msg_queue.c
*/

#include "zappy.h"

void free_msg_queue(msg_queue_t *msg_queue)
{
    msg_queue_t *current = msg_queue;
    msg_queue_t *next;
    if (msg_queue == NULL || current->next_msg == NULL) {
        msg_queue = NULL;
        return;
    }
    while (current != NULL) {
        if (current->msg != NULL) {
            free_array((void**)current->msg);
        }
        next = current->next_msg;
        free(current);
        current = next;
    }
    msg_queue = NULL;
}

void delete_last_node(msg_queue_t *msg_queue)
{
    msg_queue_t *msg = msg_queue;
    msg_queue_t *previous = msg_queue;
    if (msg->next_msg == NULL) {
        msg_queue = NULL;
        return;
    }
    while (msg->next_msg != NULL) {
        previous = msg;
        msg = msg->next_msg;
    }
    previous->next_msg = NULL;
    free(msg);
}

static void update_msg_queue(ia_t *ia, common_t *com)
{
    msg_queue_t *msg = ia->msg_queue;
    time_t now = time(NULL);
    while (msg->next_msg != NULL) {
        msg = msg->next_msg;
    }
    if (msg->start == 0) {
        msg->start = now;
        return;
    }
    if (difftime(now, msg->start) >= msg->time) {
        msg->handler(msg->msg, ia, com);
        if (ia->msg_queue->next_msg == NULL)
            ia->msg_queue = NULL;
        else
            delete_last_node(ia->msg_queue);
    }
}

void check_msg_queue_ia(common_t *com)
{
    if (com->ia == NULL)
        return;
    for (int i = 0; i < MAX_PLAYER; i++) {
        if (com->ia[i].msg_queue != NULL) {
            update_msg_queue(&com->ia[i], com);
        }
    }
}

void check_msg_queue_gui(common_t *com)
{
    msg_queue_t *msg = com->gui->msg_queue;
    time_t now;
    if (msg == NULL)
        return;
    while (msg->next_msg != NULL) {
        msg = msg->next_msg;
    }
    now = time(NULL);
    if (msg->start == 0) {
        msg->start = now;
        return;
    }
    if (difftime(now, msg->start) >= msg->time) {
        msg->handler(msg->msg, (void*)com->gui, com);
        if (com->gui->msg_queue->next_msg == NULL)
            com->gui->msg_queue = NULL;
        else
            delete_last_node(com->gui->msg_queue);
    }
}
