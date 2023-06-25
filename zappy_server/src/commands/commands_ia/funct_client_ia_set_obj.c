/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_set_obj
*/

#include "zappy.h"

/**
 @brief receive and prepare the elements needed to prepare the
 order that will be processed by the server for the command set
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure of ia
 @param char **args: the arguments receive with the command ia
 @param common_t com: structure commun -> this structure gathers
 all the server data
 @return void
**/
void funct_client_ia_set_obj(ia_t *ia, char **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    (void)args;
    (void)com;
    if (new_msg == NULL) {
        return;
    }
    new_msg->msg = malloc(sizeof(char*) * 2);
    new_msg->msg[0] = malloc(sizeof(char) * (strlen(args[0]) + 1));
    new_msg->msg[0][0] = '\0';
    new_msg->msg[0] = strcat(new_msg->msg[0], args[0]);
    new_msg->msg[1] = NULL;
    new_msg->time = 7. / (double)com->freq;
    new_msg->start = 0;
    new_msg->handler = &funct_response_ia_set_obj;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
}
