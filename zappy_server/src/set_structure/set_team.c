/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_team.c
*/

#include "teams.h"
#include <string.h>
#include <stdlib.h>

team_t set_team(char *team_name, size_t slot)
{
    team_t team;
    team.nb_slot = slot;
    team.name = malloc(sizeof(char) * (strlen(team_name) + 1));
    strcpy(team.name, team_name);
    team.actif_player = 0;
    team.players = NULL;
    return team;
}

void free_all_teams(team_t *teams, size_t nbr_teams)
{
    for (size_t i = 0; i < nbr_teams; i++) {
        //TODO - free players
        free(teams[i].name);
    }
    free(teams);
}
