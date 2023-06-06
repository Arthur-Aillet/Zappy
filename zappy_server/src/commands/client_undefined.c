/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** client_undefined.c
*/

#include "zappy.h"
#include <string.h>

//NOTE - If an egg is find the player take its position and delete the egg
// ! An egg is deleted when these positions are in x= -1 and y= -1
static void egg_position(int *x, int *y, player_t *player)
{
    for (int i = 0; i < MAX_PLAYER; i++) {
        if (player[i].egg.x != -1 && player[i].egg.y != -1) {
            *x = player[i].egg.x;
            *y = player[i].egg.y;
            player[i].egg.x = -1;
            player[i].egg.y = -1;
            break;
        }
    }
}

static int add_new_player(team_t *team, int default_x, int default_y)
{
    int x = default_x;
    int y = default_y;
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

static int check_teams_name(const char *team_name, common_t *com, int idx)
{
    for (size_t i = 0; i < com->nb_teams; i++) {
        if (strcmp(TEAM(i).name, team_name) == 0 &&
        TEAM(i).actif_player == TEAM(i).nb_slot) {
            fprintf(stderr, "%sThe team: %s%s%s is full%s\n",
                RED, BLUE,TEAM(i).name, RED, NEUTRE);
            break;
        }
        if (strcmp(TEAM(i).name, team_name) == 0) {
            int res = add_new_player(&TEAM(i), com->gui.map.height / 2, com->gui.map.width / 2);
            if (res < 0) {
                fprintf(stderr, "%sThe team: %s%s%s is full%s\n",
                RED, BLUE,TEAM(i).name, RED, NEUTRE);
                break;
            }
            printf("%sThe client %s%d%s has been registered in the team %s%s%s\n",
                GREEN, BLUE, com->client[idx].socket, GREEN, BLUE, TEAM(i).name, NEUTRE);
            com->client[idx].struct_client = (player_t*) &(TEAM(i).players[res]);
            com->client[idx].type = IA;
            return 1;
        }
    }
    return 0;
}

static int check_graphic(uint8_t **command, common_t *com, int idx)
{
    if (strcmp((char*)command[0], "GRAPHIC") != 0 || command[1] != NULL)
        return 0;
    com->client[idx].type = GUI;
    com->client[idx].struct_client = (gui_t *) &(com->gui);
    return 1;
}

int undefined_client_command(uint8_t **command, common_t *com, int idx)
{
    if (check_graphic(command, com, idx) == 1) {
        //TODO - send command msz
        //TODO - send command sgt
        //TODO - send command bct for all tiles
        write(com->client[idx].socket, "graphic command\n", 16);
    } else if (check_teams_name((char*)command[0], com, idx) == 1){
        write(com->client[idx].socket, "player command\n", 15);
        //TODO - send client num `TEAM(i).nb_slot`
        //TODO - send world's dimension
    } else {
        return error("Invalid command for defined the client", 0);
    }
    return 1;
}
