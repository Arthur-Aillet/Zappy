/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_broadcast
*/

#include "zappy.h"

static void send_message_to_players(common_t *com, char **args, ia_t *ia)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        send_message_to_player(com, ia, i, args);
    }
}

void funct_response_ia_broadcast(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    SIZE = 4;
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL)
        return;
    send_message_to_players(com, args, ia);
    OCTETS[0] = '\0';
    strcat(OCTETS, "ok\n\0");
    write(ia->buffer.sock.sockfd, OCTETS, strlen(OCTETS));
}
