/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_new_player.c
*/

#include <stdbool.h>

#include "teams.h"
#include "error_handling.h"
#include "zappy.h"

//NOTE - If an egg is find the player take its position and delete the egg
// ! An egg is deleted when these positions are in x= -1 and y= -1
static int egg_position(int *x, int *y, team_t *team)
{
    if (team->nb_eggs > 0) {
        int idx = rand() % team->nb_eggs;
        *x = team->egg[idx].x;
        *y = team->egg[idx].y;
        for (size_t i = idx; i < team->nb_eggs; i++) {
            team->egg[i].x = team->egg[i + 1].x;
            team->egg[i].y = team->egg[i + 1].y;
        }
        team->egg[team->nb_eggs - 1].x = -1;
        team->egg[team->nb_eggs - 1].y = -1;
        team->nb_eggs--;
        return team->egg[team->nb_eggs + 1].egg_id;
    }
    return 0;
}

static bool add_new_player(team_t *team, size_t max_x, size_t max_y, common_t *com)
{
    u_int8_t **args;
    char buffer_args[256];
    int status;
    bool ret = false;
    int i = 0;

    if (team->nb_slot == team->actif_player)
        return -1;
    srand(time(NULL));
    int x = rand() % max_x;
    int y = rand() % max_y;
    int o = rand() % 4;
    status = egg_position(&x, &y, team);
    for (; i < MAX_PLAYER; i++) {
        if (team->players[i].x == -1 && team->players[i].y == -1) {
            team->players[i].x = x;
            team->players[i].y = y;
            team->players[i].orientation = (size_t)o;
            team->actif_player++;
            ret = true;
            break;
        }
    }
    if (status != 0) {
        args = malloc(sizeof(u_int8_t *) * 1);
        if (args == NULL) {
            //error
        }
        sprintf(buffer_args, "%d", status);
        args[0] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
        if (args[0] == NULL) {
            //error
        }
        args[0][0] = '\0';
        strcat((char*)args[0], buffer_args);
        funct_server_ebo(args, com->gui, com);
    } else {
        args = malloc(sizeof(u_int8_t *) * 6);
        if (args == NULL) {
            //error
        }
        sprintf(buffer_args, "%d", team->players[i].id);
        args[0] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
        if (args[0] == NULL) {
            //error
        }
        args[0][0] = '\0';
        strcat((char*)args[0], buffer_args);
        sprintf(buffer_args, "%d", team->players[i].x);
        args[1] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
        if (args[1] == NULL) {
            //error
        }
        args[1][0] = '\0';
        strcat((char*)args[1], buffer_args);
        sprintf(buffer_args, "%d", team->players[i].y);
        args[2] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
        if (args[2] == NULL) {
            //error
        }
        args[2][0] = '\0';
        strcat((char*)args[2], buffer_args);
        sprintf(buffer_args, "%ld", team->players[i].orientation);
        args[3] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
        if (args[3] == NULL) {
            //error
        }
        args[3][0] = '\0';
        strcat((char*)args[3], buffer_args);
        sprintf(buffer_args, "%ld", team->players[i].level);
        args[4] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
        if (args[4] == NULL) {
            //error
        }
        args[4][0] = '\0';
        strcat((char*)args[4], buffer_args);
        args[5] = malloc(sizeof(u_int8_t) * strlen(team->name));
        if (args[5] == NULL) {
            //error
        }
        args[5][0] = '\0';
        strcat((char*)args[5], team->name);
        funct_server_pnw(args, com->gui, com);
    }
    return ret;
}

int check_slot_and_create_player(common_t *com, int t_idx,int client_idx)
{
    srand(time(NULL));
    bool res = add_new_player(&TEAM(t_idx), com->gui->map.height,
                            com->gui->map.width, com);
    if (res == false) {
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