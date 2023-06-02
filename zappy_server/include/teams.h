/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** teams.h
*/

#ifndef TEAMS_H_
    #define TEAMS_H_

    #include "common.h"

    #include <stdio.h>

enum orientation {
    Nord = 1,
    Est = 2,
    Sud = 3,
    West = 4,
};

typedef struct egg_s {
    int egg_id;
    size_t x;
    size_t y;
} egg_t;

typedef struct player_s {
    int id;
    size_t x;
    size_t y;
    size_t orientation;
    size_t level;
    size_t life;
    size_t satiety;         //NOTE - if satiety == 0 then decrease life
    size_t *inventory;
    egg_t egg;
} player_t;

typedef struct team_s {
    char *name;
    size_t nb_slot;         //NOTE - max number of player in this team (can be increased with an egg)
    size_t actif_player;
    player_t *players;
} team_t;

team_t set_team(char *team_name, size_t slot);
void free_all_teams(team_t* teams, size_t nbr_teams);

#endif /* !TEAMS_H_ */