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

/**
 * @brief Set a player and these values
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param size_t x: position of the player in x
 * @param size_t y: position of the player in y
 * @param size_t freq: frequency of the player
 * @return player
*/
player_t set_player(size_t x, size_t y, size_t freq)
{
    player_t new;

    new.x = x;
    new.y = y;
    new.id = rand();
    new.orientation = 1 + rand() % 4;
    new.level = 1;
    new.life = 10;
    new.start = time(NULL);
    new.time = 126. / (double)freq;
    new.incantation = NO;
    new.inventory = malloc(sizeof(size_t) * 8);
    if (new.inventory == NULL) {
        error("Couldn't allocate inventory", 0);
        return new;
    }
    for (size_t i = 0; i < 8; i++)
        new.inventory[i] = 0;
    return new;
}

/**
 * @brief reset player data
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param player_t *player: the player reset
 * @param int freq: the frequency of all actions in the game
 * @return int
*/
void reset_player(player_t *player, size_t freq)
{
    if (player->inventory != NULL)
        free(player->inventory);
    *player = set_player(-1, -1, freq);
}

/**
 * @brief free all players
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param team_t *team: the array of all teams
 * @return void
*/
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
