/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** create_struct_client.c
*/

#include "zappy.h"

ia_t *find_ia_for_command(common_t *com, client_t *client)
{
    player_t *player = (player_t *)client->str_cli;

    for (size_t tmp = 0; tmp < MAX_CLIENTS; tmp++) {
        if (com->ia[tmp].player == NULL)
            continue;
        if (com->ia[tmp].player->id == player->id) {
            return &com->ia[tmp];
        }
    }
    return NULL;
}
