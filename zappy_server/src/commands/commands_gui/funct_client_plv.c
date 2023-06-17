/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_plv
*/

#include "zappy.h"

void funct_client_plv(gui_t *gui, uint8_t **args, common_t *com)
{
    msg_queue_t new_msg;

    (void)com;
    new_msg.time = 0;
    new_msg.msg = malloc(sizeof(u_int8_t *) * 2);
    if (new_msg.msg == NULL) {
        //error
        return;
    }
    new_msg.msg[0] = malloc(sizeof(u_int8_t) *
                    (strlen((char*)args[0]) + 1));
    if (new_msg.msg[0] == NULL) {
        //error
        return;
    }
    new_msg.msg[0][0] = '\0';
    new_msg.msg[0] = (uint8_t*)strcat((char*)new_msg.msg[0], (char*)args[0]);
    new_msg.handler = &funct_server_plv;
    new_msg.next_msg = gui->msg_queue;
    printf("rentrer dans la funct_client_plv\n");
}
