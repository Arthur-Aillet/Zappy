/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** update_life.c
*/

#include "teams.h"
#include "server.h"
#include "error_handling.h"
#include <stdlib.h>

static int update_player_life(player_t *player)
{
    if (player->x == -1 && player->y == -1)
        return 1;
    time_t now = time(NULL);
    if (difftime(now, player->start) >= player->time) {
        if (player->inventory[FOOD] == 0)
            player->life--;
        else
            player->inventory[FOOD]--;
        if (player->life == 0) {
            //TODO - send death message
            //FIXME il faut que le player est accès à la structure client via un pointeur
            return 0;
        }
        player->start = time(NULL);
    }
    return 1;
}

void reset_player(player_t *player, size_t freq)
{
    if (player->inventory != NULL)
        free(player->inventory);
    *player = set_player(-1, -1, freq);
}

void update_life(client_t *client, server_t *server, size_t freq)
{
    (void)server;
    int res = 1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client->type == IA) {
            res = update_player_life((player_t *)client->str_cli);
        }
        if (client->type == IA && res == 0) {
            res = 1;
            reset_player((player_t *)client->str_cli, freq);
            //FIXME close_client(client->socket, server);
        }
    }
}
