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

egg_t set_egg(int x, int y)
{
    egg_t new;
    new.x = x;
    new.y = y;
    return new;
}

player_t set_player(size_t x, size_t y)
{
    srand(time(NULL));
    player_t new;
    new.x = x;
    new.y = y;
    new.orientation = 1 + rand() % 5;
    new.level = 1;
    new.life = 10;
    new.satiety = 10;
    new.egg = set_egg(-1, -1);
    new.inventory = malloc(sizeof(size_t) * 7);
    for (size_t i = 0; i < 7; i++)
        new.inventory[i] = 0;
    return new;
}

team_t set_team(char *team_name, size_t slot)
{
    team_t team;
    team.nb_slot = slot;
    team.name = malloc(sizeof(char) * (strlen(team_name) + 1));
    strcpy(team.name, team_name);
    team.actif_player = 0;
    team.players = malloc(sizeof(player_t) * MAX_PLAYER);
    return team;
}

//TODO - free players
void free_all_teams(team_t *teams, size_t nbr_teams)
{
    for (size_t i = 0; i < nbr_teams; i++) {
        free(teams[i].name);
    }
    free(teams);
}
