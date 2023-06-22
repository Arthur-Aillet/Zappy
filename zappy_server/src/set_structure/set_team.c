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

void delete_egg(egg_t *egg, int nb_valid_egg)
{
    egg_t *e = malloc(sizeof(egg_t) * nb_valid_egg);
    int new_i = 0;

    for (int i = 0; i < nb_valid_egg; i++) {
        if (egg[i].x == -1 && egg[i].y == -1)
            continue;
        e[new_i] = egg[i];
        new_i++;
    }
    egg = realloc(egg, sizeof(egg_t) * nb_valid_egg);
    new_i = 0;
    for (int i = 0; i < nb_valid_egg; i++) {
        if (egg[i].x == -1 && egg[i].y == -1)
            continue;
        egg[new_i] = e[i];
        new_i++;
    }
    free(e);
}

egg_t set_egg(int x, int y)
{
    egg_t new;

    new.x = x;
    new.y = y;
    new.egg_id = rand();
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

void free_all_teams(team_t *teams, size_t nbr_teams)
{
    for (size_t i = 0; i < nbr_teams; i++) {
        free_all_players(&teams[i]);
        free(teams[i].name);
    }
    free(teams);
    basic_log("Teams free", B, 0);
}
