/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** update_life.c
*/

#include <stdlib.h>

#include "zappy.h"
#include "error_handling.h"

static ia_t *to_find_ia_int(int id, common_t *common)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (common->ia[i].player != NULL && id == common->ia[i].player->id) {
            return &common->ia[i];
        }
    }
    return NULL;
}

static int player_is_dead(player_t *player, common_t *com)
{
    char buffer_args[256];
    uint8_t **args = malloc(sizeof(uint8_t *) * 2);
    ia_t *ia = to_find_ia_int(player->id, com);

    if (args == NULL)
        return error("Memory allocation failed", 0);
    if (ia == NULL)
        return error("Bad player id", 0);

    *ia = close_ia();
    if (args == NULL)
        return error("Memory allocation failed", 0);
    sprintf(buffer_args, "%d", player->id);
    args[0] = malloc(sizeof(uint8_t) * strlen(buffer_args) + 1);
    if (args[0] == NULL)
        return error("Memory allocation failed", 0);
    args[0][0] = '\0';
    args[1] = NULL;
    strcat((char*)args[0], buffer_args);
    funct_server_pdi(args, com->gui, com);
    funct_response_ia_death(args, ia, com);
    return 1;
}

//FIXME il faut que le player est accès à la structure client via un pointeur
static int update_player_life(player_t *player, common_t *com)
{
    time_t now = time(NULL);

    if (player->x == -1 && player->y == -1)
        return 1;
    if (difftime(now, player->start) >= player->time) {
        if (player->inventory[FOOD] == 0)
            player->life--;
        else
            player->inventory[FOOD]--;
        if (player->life == 0) {
            player_is_dead(player, com);
            close_player(player);
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

//FIXME close_client(client->socket, server);
void update_life(client_t *client, server_t *server, size_t freq, common_t *com)
{
    (void)server;
    int res = 1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client->type == IA) {
            res = update_player_life((player_t *)client->str_cli, com);
        }
        if (client->type == IA && res == 0) {
            res = 1;
            reset_player((player_t *)client->str_cli, freq);
        }
    }
}
