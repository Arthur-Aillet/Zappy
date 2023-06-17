/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_fork
*/

#include "zappy.h"

void funct_client_ia_fork(ia_t *ia, uint8_t **args, common_t *com)
{
    msg_queue_t new_msg;
    u_int8_t **arg = malloc(sizeof(u_int8_t *) * 1);
    char buffer_player[256];

    if (arg == NULL) {
        //error
    } else {
        sprintf(buffer_player, "%d", ia->player->id);
        arg[0] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[0] == NULL) {
            //error
        }
        arg[0][0] = '\0';
        strcat((char*)arg[0], buffer_player);
    }
    new_msg.time = 42;
    new_msg.handler = &funct_response_ia_fork;
    new_msg.next_msg = ia->msg_queue;
    funct_server_pfk(arg, com->gui, com);
    printf("rentrer dans la funct_client_ia_fork");
    (void)ia;
    (void)args;
    (void)new_msg;
}
