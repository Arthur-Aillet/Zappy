/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_player.c
*/

#include "teams.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "error_handling.h"

player_t set_player(size_t x, size_t y, size_t freq)
{
    player_t new;

    new.x = x;
    new.y = y;
    new.id = rand();
    new.orientation = 1 + rand() % 5;
    new.level = 1;
    new.life = 10;
    new.satiety = 10;
    new.start = time(NULL);
    new.time = 126 / freq;
    new.inventory = malloc(sizeof(size_t) * 7);
    if (new.inventory == NULL) {
        error("Couldn't allocate inventory", 0);
        return new;
    }
    for (size_t i = 0; i < 7; i++)
        new.inventory[i] = 0;
    return new;
}

void close_player(player_t *player)
{
    player->id = -1;
    player->incantation = NO;
    for (size_t i = 0; i < 7; i++)
        player->inventory[i] = 0;
    player->level = 1;
    player->life = 0;
    player->orientation = Unknown;
}

void free_all_players(team_t * team)
{
    if (team->players == NULL)
        return;
    for (int i = 0; i < MAX_PLAYER; i++)
        if (team->players[i].inventory != NULL)
            free(team->players[i].inventory);
    free(team->players);
    basic_log("Players free", B, 0);
}
