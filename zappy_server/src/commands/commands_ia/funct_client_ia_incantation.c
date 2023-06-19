/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_incantation
*/

#include "zappy.h"

//voir avec ludo comment faire pour appeler la fonction enfin la partie du gui qu'il faut
// et voir si on verifie dans la fonction ici ou dans le pic pour les besoins de l'incantation

void funct_client_ia_incantation(ia_t *ia, uint8_t **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    (void)com;
    (void)args;
    if (new_msg == NULL) {
        //error
        return;
    }
    new_msg->time = 300;
    new_msg->handler = &funct_response_ia_incantation;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
    //funct_server_pic();
    printf("rentrer dans la funct_client_ia_incantation");
}
