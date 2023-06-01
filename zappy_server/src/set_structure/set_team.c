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
    team.name = malloc(sizeof(uint8_t) * strlen(team_name));
    team.name = (uint8_t*)team_name;
    printf("team_name = %s", (char*)team.name);
    team.actif_player = 0;
    team.players = NULL;
    return team;
}
