/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** teams.h
*/

#ifndef TEAMS_H_
    #define TEAMS_H_

    #define MAX_PLAYER     20
    #include "common.h"

    #include <stdio.h>

enum orientation {
    North = 1,
    Right = 2,
    Left = 3,
    West = 4,
};

typedef struct egg_s {
    int egg_id;
    int x;
    int y;
} egg_t;

typedef struct player_s {
    int id;
    int x;
    int y;
    time_t start;
    double time;
    size_t orientation;
    size_t life;
    size_t level;
    size_t satiety;         //NOTE - if satiety == 0 then decrease life
    size_t *inventory;
} player_t;

typedef struct team_s {
    char *name;
    size_t nb_slot;         //NOTE - max number of player in this team (can be increased with an egg)
    size_t actif_player;
    size_t nb_eggs;
    player_t *players;
    egg_t *egg;
} team_t;

player_t set_player(size_t x, size_t y, size_t freq);
team_t set_team(char *team_name, size_t slot, size_t freq);

void free_all_teams(team_t* teams, size_t nbr_teams);

void reset_player(player_t *player, size_t freq);

#endif /* !TEAMS_H_ */
