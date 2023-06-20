/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_client_ia_incantation
*/

#include "zappy.h"

static int to_find_ia_incantation(common_t *com, ia_t *ia)
{
    team_t *team = to_find_team_by_int(ia->player->id, com);

    for (size_t tmp = 0; tmp < team->actif_player; tmp++) {
        if (ia->player->x == team->players[tmp].x && ia->player->y == team->players[tmp].y && ia->player->level == team->players[tmp].level && ia->player->id != team->players[tmp].id && team->players[tmp].incantation == NO) {
            team->players[tmp].incantation = FOLLOWER;
            return team->players[tmp].id;
        }
    }
    for (size_t tmp = 0; tmp < com->nb_ia; tmp++) {
        if (ia->player->x == com->ia[tmp].player->x && ia->player->y == com->ia[tmp].player->y && ia->player->level == com->ia[tmp].player->level && ia->player->id != com->ia[tmp].player->id && team->players[tmp].incantation == NO) {
            com->ia[tmp].player->incantation = FOLLOWER;
            return com->ia[tmp].player->id;
        }
    }
    return -1;
}

static void call_function_gui(ia_t *ia, common_t *com)
{
    u_int8_t **arg;
    int result_ia = 0;
    char buffer_player[256];

    if (ia->player->level == 1) {
        arg = malloc(sizeof(u_int8_t *) * 4);
        if (arg == NULL) {
            return;
        }
        sprintf(buffer_player, "%d", ia->player->x);
        arg[0] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[0] == NULL) {
        }
        arg[0][0] = '\0';
        strcat((char*)arg[0], buffer_player);
        sprintf(buffer_player, "%d", ia->player->y);
        arg[1] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[1] == NULL) {
        }
        arg[1][0] = '\0';
        strcat((char*)arg[1], buffer_player);
        sprintf(buffer_player, "%ld", ia->player->level);
        arg[2] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[2] == NULL) {
        }
        arg[2][0] = '\0';
        strcat((char*)arg[2], buffer_player);
        sprintf(buffer_player, "%d", ia->player->id);
        arg[3] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[3] == NULL) {
        }
        arg[3][0] = '\0';
        strcat((char*)arg[3], buffer_player);
        funct_server_pic(arg, com->gui, com);
    } else if (ia->player->level == 2 || ia->player->level == 3) {
        arg = malloc(sizeof(u_int8_t *) * 5);
        if (arg == NULL) {
            return;
        }
        sprintf(buffer_player, "%d", ia->player->x);
        arg[0] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[0] == NULL) {
        }
        arg[0][0] = '\0';
        strcat((char*)arg[0], buffer_player);
        sprintf(buffer_player, "%d", ia->player->y);
        arg[1] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[1] == NULL) {
        }
        arg[1][0] = '\0';
        strcat((char*)arg[1], buffer_player);
        sprintf(buffer_player, "%ld", ia->player->level);
        arg[2] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[2] == NULL) {
        }
        arg[2][0] = '\0';
        strcat((char*)arg[2], buffer_player);
        sprintf(buffer_player, "%d", ia->player->id);
        arg[3] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[3] == NULL) {
        }
        arg[3][0] = '\0';
        strcat((char*)arg[3], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[4] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[4] == NULL) {
        }
        arg[4][0] = '\0';
        strcat((char*)arg[4], buffer_player);
        funct_server_pic(arg, com->gui, com);
    } else if (ia->player->level == 4 || ia->player->level == 5) {
        arg = malloc(sizeof(u_int8_t *) * 7);
        if (arg == NULL) {
            return;
        }
        sprintf(buffer_player, "%d", ia->player->x);
        arg[0] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[0] == NULL) {
        }
        arg[0][0] = '\0';
        strcat((char*)arg[0], buffer_player);
        sprintf(buffer_player, "%d", ia->player->y);
        arg[1] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[1] == NULL) {
        }
        arg[1][0] = '\0';
        strcat((char*)arg[1], buffer_player);
        sprintf(buffer_player, "%ld", ia->player->level);
        arg[2] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[2] == NULL) {
        }
        arg[2][0] = '\0';
        strcat((char*)arg[2], buffer_player);
        sprintf(buffer_player, "%d", ia->player->id);
        arg[3] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[3] == NULL) {
        }
        arg[3][0] = '\0';
        strcat((char*)arg[3], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[4] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[4] == NULL) {
        }
        arg[4][0] = '\0';
        strcat((char*)arg[4], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[5] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[5] == NULL) {
        }
        arg[5][0] = '\0';
        strcat((char*)arg[5], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[6] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[6] == NULL) {
        }
        arg[6][0] = '\0';
        strcat((char*)arg[6], buffer_player);
        funct_server_pic(arg, com->gui, com);
    } else {
        arg = malloc(sizeof(u_int8_t *) * 9);
        if (arg == NULL) {
            return;
        }
        sprintf(buffer_player, "%d", ia->player->x);
        arg[0] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[0] == NULL) {
        }
        arg[0][0] = '\0';
        strcat((char*)arg[0], buffer_player);
        sprintf(buffer_player, "%d", ia->player->y);
        arg[1] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[1] == NULL) {
        }
        arg[1][0] = '\0';
        strcat((char*)arg[1], buffer_player);
        sprintf(buffer_player, "%ld", ia->player->level);
        arg[2] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[2] == NULL) {
        }
        arg[2][0] = '\0';
        strcat((char*)arg[2], buffer_player);
        sprintf(buffer_player, "%d", ia->player->id);
        arg[3] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[3] == NULL) {
        }
        arg[3][0] = '\0';
        strcat((char*)arg[3], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[4] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[4] == NULL) {
        }
        arg[4][0] = '\0';
        strcat((char*)arg[4], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[5] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[5] == NULL) {
        }
        arg[5][0] = '\0';
        strcat((char*)arg[5], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[6] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[6] == NULL) {
        }
        arg[6][0] = '\0';
        strcat((char*)arg[6], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[7] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[7] == NULL) {
        }
        arg[7][0] = '\0';
        strcat((char*)arg[7], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[8] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[8] == NULL) {
        }
        arg[8][0] = '\0';
        strcat((char*)arg[8], buffer_player);
        funct_server_pic(arg, com->gui, com);
    }
}

void funct_client_ia_incantation(ia_t *ia, uint8_t **args, common_t *com)
{
    msg_queue_t *new_msg = malloc(sizeof(msg_queue_t));

    (void)com;
    (void)args;
    if (new_msg == NULL) {
        return;
    }
    if (com->gui->map.tiles[ia->player->x][ia->player->y].nb_player_incantations) { //voir condition pour rentrer dedans
        call_function_gui(ia, com);
    }
    new_msg->time = 300;
    new_msg->handler = &funct_response_ia_incantation;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
    printf("rentrer dans la funct_client_ia_incantation");
}
