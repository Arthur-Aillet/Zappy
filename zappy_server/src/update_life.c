/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** update_life.c
*/

#include <stdlib.h>

#include "zappy.h"
#include "error_handling.h"

client_t *find_client_by_id(int id, common_t *com)
{
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (com->client[i].str_cli == NULL || com->client[i].type != IA)
            continue;
        player_t *player = (player_t*)&com->client[i].str_cli;
        if (player->id == id)
            return &com->client[i];
    }
    return NULL;
}

static int player_is_dead(player_t *player, common_t *com)
{
    ia_t *ia = to_find_ia_int(player->id, com);
    team_t *team = to_find_team_by_int(player->id, com);

    if (ia == NULL || team == NULL)
        return error("Bad player id", 0);

    team->actif_player -= 1;
    *ia = close_ia();
    return 1;
}

static void send_pdi(player_t *player, common_t *com)
{
    char **args = malloc(sizeof(char*) * 2);
    ia_t *ia = to_find_ia_int(player->id, com);

    if (args == NULL || ia == NULL) {
        return;
    }
    char buffer[256];
    sprintf(buffer, "%d", player->id);
    args[0] = malloc(sizeof(char) * (strlen(buffer) + 2));
    args[0][0] = '\0';
    args[1] = NULL;
    sprintf(args[0], "%d", player->id);
    funct_server_pdi(args, (void*)com->gui, NULL);
    funct_response_ia_death(args, ia, com);
    free_array((void **)args);
}

static int update_player_life(player_t *player, common_t *com)
{
    time_t now = time(NULL);

    if (player->x == -1 && player->y == -1)
        return error("Player not initialized", 0);
    if (player->life > 0 && player->life < 10 && player->inventory[FOOD] > 0) {
        player->life++;
        player->inventory[FOOD]--;
    }
    if (difftime(now, player->start) >= player->time) {
        if (player->inventory[FOOD] == 0)
            player->life--;
        else
            player->inventory[FOOD]--;
        if (player->life == 0) {
            send_pdi(player, com);
            return player_is_dead(player, com);
        } else
            player->start = time(NULL);
    }
    return 0;
}

void update_life(client_t *client, server_t *server, size_t freq, common_t *com)
{
    int res = 0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client[i].type == IA) {
            res = update_player_life((player_t *)client[i].str_cli, com);
        }
        if (client[i].type == IA && res == 1) {
            res = 0;
            client[i].type = UNDEFINED;
            reset_player((player_t *)client->str_cli, freq);
            client[i].socket = close_client(client[i].socket, server);
        }
    }
}
