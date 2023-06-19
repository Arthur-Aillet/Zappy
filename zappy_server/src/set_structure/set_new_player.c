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

static void send_to_gui_buffer(int num, char *value, uint8_t *arg)
{
    char buffer_args[256];

    if (value == NULL)
        sprintf(buffer_args, "%d", num);
    else
        sprintf(buffer_args, "%s", value);
    arg = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (arg == NULL)
        error("Memory allocation failed", 0);
    arg[0] = '\0';
    strcat((char*)arg, buffer_args);
}

static void send_to_gui(int status, common_t *com, team_t *team, int i)
{
    uint8_t **args;

    if (status != 0) {
        args = malloc(sizeof(u_int8_t *) * 1);
        if (args == NULL)
            error("Memory allocation failed", 0);
        send_to_gui_buffer(status, NULL, args[0]);
        funct_server_ebo(args, com->gui, com);
    } else {
        args = malloc(sizeof(u_int8_t *) * 6);
        if (args == NULL)
            error("Memory allocation failed", 0);
        send_to_gui_buffer(team->players[i].id, NULL, args[0]);
        send_to_gui_buffer(team->players[i].x, NULL, args[1]);
        send_to_gui_buffer(team->players[i].y, NULL, args[2]);
        send_to_gui_buffer(team->players[i].orientation, NULL, args[3]);
        send_to_gui_buffer(team->players[i].level, NULL, args[4]);
        send_to_gui_buffer(0, team->name, args[5]);
        funct_server_pnw(args, com->gui, com);
    }
}

static bool add_new_player(team_t *team, size_t max_x, size_t max_y,
                            common_t *com)
{
    bool ret = false;
    int i = 0;
    int status;
    int x = rand() % max_x;
    int y = rand() % max_y;

    if (team->nb_slot == team->actif_player)
        return false;
    status = egg_position(&x, &y, team);
    for (; i < MAX_PLAYER; i++) {
        if (team->players[i].x == -1 && team->players[i].y == -1) {
            team->players[i].x = x;
            team->players[i].y = y;
            team->players[i].orientation = rand() % 4;
            team->actif_player++;
            ret = true;
            break;
        }
    }
    send_to_gui(status, com, team, i);
    return ret;
}

int check_slot_and_create_player(common_t *com, int t_idx,int client_idx)
{
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
