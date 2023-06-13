/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_new_player.c
*/

#include "teams.h"
#include "error_handling.h"
#include "zappy.h"

//NOTE - If an egg is find the player take its position and delete the egg
// ! An egg is deleted when these positions are in x= -1 and y= -1
static void egg_position(int *x, int *y, team_t *team)
{
    if (team->nb_eggs > 0) {
        int idx = rand() % team->nb_eggs;
        *x = team->egg[idx].x;
        *y = team->egg[idx].y;
        for (int i = idx; i < team->nb_eggs; i++) {
            team->egg[i].x = team->egg[i + 1].x;
            team->egg[i].y = team->egg[i + 1].y;
        }
        team->egg[team->nb_eggs - 1].x = -1;
        team->egg[team->nb_eggs - 1].y = -1;
        team->nb_eggs--;
    }
}

static int add_new_player(team_t *team, size_t max_x, size_t max_y)
{
    if (team->nb_slot == team->actif_player)
        return -1;
    srand(time(NULL));
    int x = rand() % max_x;
    int y = rand() % max_y;
    egg_position(&x, &y, team->players);
    for (int i = 0; i < MAX_PLAYER; i++) {
        if (team->players[i].x == -1 && team->players[i].y == -1) {
            team->players[i].x = x;
            team->players[i].y = y;
            team->actif_player++;
            return i;
        }
    }
    return -1;
}

int check_slot_and_create_player(common_t *com, int t_idx,int client_idx)
{
    srand(time(NULL));
    int res = add_new_player(&TEAM(t_idx), com->gui->map.height,
                            com->gui->map.width);
    if (res < 0) {
        fprintf(stderr, "%sThe team: %s%s%s is full%s\n",
        R, B,TEAM(t_idx).name, R, N);
        return 0;
    }
    printf("%sThe client %s%d%s has been registered in the team %s%s%s\n",
        G, B, com->client[client_idx].socket, G, B, TEAM(t_idx).name, N);
    com->client[client_idx].str_cli = (player_t*) &(TEAM(t_idx).players[res]);
    com->client[client_idx].type = IA;
    return 1;
}