/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_sgt
*/

#include "zappy.h"

void funct_client_ia_msg(ia_t *ia, uint8_t **args)
{
    msg_queue_t new_msg;

    new_msg.time = 0;
    new_msg.msg = malloc(sizeof(u_int8_t *) * 3);
    if (new_msg.msg == NULL) {
        //error
        return NULL;
    }
    new_msg.msg[0] = malloc(sizeof(u_int8_t) *
                    (strlen(args[0]) + 1));
    if (new_msg.msg[0] == NULL) {
        //error
        return NULL;
    }
    new_msg.msg[0][0] = '\0';
    new_msg.msg[0] = strcat(new_msg.msg[0], args[0]);
    new_msg.msg[1] = malloc(sizeof(u_int8_t) *
                    (strlen(args[1] + 1)));
    if (new_msg.msg[0] == NULL) {
        //error
        return NULL;
    }
    new_msg.msg[1][0] = '\0';
    new_msg.msg[1] = strcat(new_msg.msg[0], args[1]);
    new_msg.msg[2] = NULL;
    new_msg.handler = &funct_response_ia_msg;
    new_msg.next_msg = ia->msg_queue;
    printf("rentrer dans la funct_client_ia_msg");
}
