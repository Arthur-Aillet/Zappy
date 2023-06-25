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

static void* send_to_gui_buffer(int num, char *value, char **arg)
{
    char buffer_args[256];
    if (value == NULL)
        sprintf(buffer_args, "%d", num);
    else
        sprintf(buffer_args, "%s", value);
    *arg = malloc(sizeof(char) * (strlen(buffer_args) + 1));
    if (*arg == NULL)
        error("Memory allocation failed", 0);
    *arg[0] = '\0';
    strcat(*arg, buffer_args);
    return NULL;
}

static void send_to_gui(int status, common_t *com, team_t *team, int i)
{
    char **args;
    if (i == -1)
        return;
    args = (status != 0) ? malloc(sizeof(char *) * 2) :
                            malloc(sizeof(char *) * 7);
    if (args == NULL)
        error("Memory allocation failed", 0);
    if (status != 0) {
        args[1] = send_to_gui_buffer(status, NULL, &args[0]);
        funct_server_ebo(args, com->gui, com);
    } else {
        send_to_gui_buffer(team->players[i].id, NULL, &args[0]);
        send_to_gui_buffer(team->players[i].x, NULL, &args[1]);
        send_to_gui_buffer(team->players[i].y, NULL, &args[2]);
        send_to_gui_buffer(team->players[i].orientation, NULL, &args[3]);
        send_to_gui_buffer(team->players[i].level, NULL, &args[4]);
        args[6] = send_to_gui_buffer(0, team->name, &args[5]);
        funct_server_pnw(args, com->gui, com);
    }
    free_array((void **)args);
}

static int add_new_player(team_t *team, size_t max_x, size_t max_y,
                            common_t *com)
{
    int ret = -1;
    int i = 0;
    int status;
    int x = rand() % max_x;
    int y = rand() % max_y;
    if (team->nb_slot == team->actif_player)
        return -1;
    status = egg_position(&x, &y, team);
    for (; i < MAX_PLAYER; i++) {
        if (team->players[i].x == -1 && team->players[i].y == -1) {
            team->players[i] = set_player(x, y, com->freq);
            team->actif_player++;
            ret = i;
            break;
        }
    }
    send_to_gui(status, com, team, i);
    return ret;
}

int check_slot_and_create_player(common_t *com, int t_idx,int client_idx)
{
    int res = add_new_player(&TEAM(t_idx), com->gui->map.height,
                            com->gui->map.width, com);
    player_t *player = (player_t*) &(TEAM(t_idx).players[res]);
    com->client[client_idx].str_cli = player;
    com->client[client_idx].type = IA;
    com->nb_ia++;
    for (int i = 0; i < MAX_PLAYER; i++) {
        if (com->ia[i].player == NULL) {
            com->ia[i].player = player;
            com->ia[i].buffer.sock.sockfd = com->client[client_idx].socket;
            com->ia[i].buffer.sock.addr = com->client[client_idx].addr;
            break;
        }
    }
    printf("%sThe client %s%d%s has been registered in the team %s%s%s "\
    "with the id %s%d%s\n", G, B, com->client[client_idx].socket, G, B,
    TEAM(t_idx).name, G, B, player->id, N);
    return 1;
}
