/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_mct
*/

#include "zappy.h"

/**
 @brief receive and prepare the elements needed to prepare the
        order that will be processed by the server for the command mct
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param gui_t *gui : structure of gui
 @param char **args: the arguments receive with the command gui -> NULL
                because there are no parameters for this command
 @param common_t com : structure commun -> this structure gathers all
                    the server data -> not use
 @return void
**/
void funct_client_mct(gui_t *gui, char **args, common_t *com)
{
    (void)args;
    (void)com;
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    if (new_msg == NULL) {
        return;
    }
    new_msg->time = 0;
    new_msg->start = 0;
    new_msg->msg = NULL;
    new_msg->handler = &funct_server_all_bct;
    new_msg->next_msg = gui->msg_queue;
    gui->msg_queue = new_msg;
}
