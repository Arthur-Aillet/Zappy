/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_team.c
*/

#include "teams.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "error_handling.h"

egg_t set_egg(int x, int y)
{
    egg_t new;

    new.x = x;
    new.y = y;
    new.egg_id = rand();
    return new;
}

player_t set_player(size_t x, size_t y, size_t freq)
{
    player_t new;

    new.x = x;
    new.y = y;
    new.id = rand();
    new.orientation = 1 + rand() % 5;
    new.life = 10;
    new.satiety = 10;
    new.start = time(NULL);
    new.time = 126 / freq;
    new.inventory = malloc(sizeof(size_t) * 7);
    for (size_t i = 0; i < 7; i++)
        new.inventory[i] = 0;
    return new;
}

team_t set_team(char *team_name, size_t slot, size_t freq)
{
    team_t team;

    team.nb_slot = slot;
    team.egg = NULL;
    team.nb_eggs = 0;
    team.name = malloc(sizeof(char) * (strlen(team_name) + 1));
    strcpy(team.name, team_name);
    team.actif_player = 0;
    team.players = malloc(sizeof(player_t) * MAX_PLAYER);
    for (int i = 0; i < MAX_PLAYER; i++)
        team.players[i] = set_player(-1, -1, freq);
    return team;
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

void free_all_teams(team_t *teams, size_t nbr_teams)
{
    for (size_t i = 0; i < nbr_teams; i++) {
        free_all_players(&teams[i]);
        free(teams[i].name);
    }
    free(teams);
    basic_log("Teams free", B, 0);
}
