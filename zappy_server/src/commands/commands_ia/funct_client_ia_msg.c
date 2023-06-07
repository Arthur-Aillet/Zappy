/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_sgt
*/

#include "zappy.h"
#include <string.h>

void funct_client_ia_msg(ia_t *ia, uint8_t **args)
{
    msg_queue_t new_msg;

    new_msg.time = 0;
    new_msg.msg = malloc(sizeof(u_int8_t *) * 3);
    if (new_msg.msg == NULL) {
        //error
        return;
    }
    new_msg.msg[0] = malloc(sizeof(u_int8_t) *
                    ( + 1));
    if (new_msg.msg[0] == NULL) {
        //error
        return;
    }
    new_msg.msg[0][0] = '\0';
    new_msg.msg[0] = (u_int8_t*)strcat((char*)new_msg.msg[0], (char*)args[0]);
    new_msg.msg[1] = malloc(sizeof(u_int8_t) *
                    (strlen((char*)args[1]) + 1));
    if (new_msg.msg[0] == NULL) {
        //error
        return;
    }
    new_msg.msg[1][0] = '\0';
    new_msg.msg[1] = (uint8_t*)strcat((char*)new_msg.msg[0], (char*)args[1]);
    new_msg.msg[2] = NULL;
    new_msg.handler = &funct_response_ia_msg;
    new_msg.next_msg = ia->msg_queue;
    printf("rentrer dans la funct_client_ia_msg");
    (void)ia;
    (void)args;
    (void)new_msg;
}
