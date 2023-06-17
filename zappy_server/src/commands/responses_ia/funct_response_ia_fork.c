/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_fork
*/

#include "zappy.h"

static team_t *to_find_team(int n, common_t *common)
{
    for (size_t i = 0; i < common->nb_teams; i++) {
        for (size_t y = 0; y < common->teams[i].actif_player; y++) {
            if (n == common->teams[i].players[y].id) {
                return &common->teams[i];
            }
        }
    }
    return NULL;
}

static egg_t *to_add_new_egg(ia_t *ia, team_t *team)
{
    team->egg[team->nb_eggs + 1] = set_egg(ia->player->x, ia->player->y);
    return team->egg;
}

void funct_response_ia_fork(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    team_t *team = to_find_team(ia->player->id, com);
    u_int8_t **arg = malloc(sizeof(u_int8_t *) * 4);
    char buffer_args[256];

    (void)args;
    (void)com;
    if (arg == NULL) {
        //error
    }
    team->egg = realloc(team->egg, sizeof(egg_t) * (team->nb_eggs + 1));
    if (team->egg == NULL) {
        //error;
    }
    team->egg = to_add_new_egg(ia, team);
    team->nb_eggs += 1;
    team->nb_slot += 1;
    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)ia->buffer.bufferWrite.octets, "ok\n\0");
    sprintf(buffer_args, "%d", team->egg[team->nb_eggs].egg_id);
    arg[0] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (arg[0] == NULL) {
        //error
    }
    arg[0][0] = '\0';
    strcat((char*)arg[0], buffer_args);
    sprintf(buffer_args, "%d", ia->player->id);
    arg[1] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (arg[1] == NULL) {
        //error
    }
    arg[1][0] = '\0';
    strcat((char*)arg[1], buffer_args);
    sprintf(buffer_args, "%d", ia->player->x);
    arg[2] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (arg[2] == NULL) {
        //error
    }
    arg[2][0] = '\0';
    strcat((char*)arg[2], buffer_args);
    sprintf(buffer_args, "%d", ia->player->y);
    arg[3] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (arg[3] == NULL) {
        //error
    }
    arg[3][0] = '\0';
    strcat((char*)arg[3], buffer_args);
    funct_server_enw(arg, com->gui, com);
    //"enw e n X Y\n"
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets, ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_fork\n");
}
