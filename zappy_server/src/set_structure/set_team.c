/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_team.c
*/

#include "teams.h"

team_t set_team(char *team_name, size_t slot)
{
    team_t team;
    team.nb_slot = slot;
    team.name = team_name;
    team.actif_player = 0;
    team.players = NULL;
    return team;
}