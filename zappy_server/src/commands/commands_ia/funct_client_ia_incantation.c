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

static void to_create_message_response_ia(msg_queue_t *new_msg)
{
    new_msg->msg = malloc(sizeof(uint8_t *) * 1);
    if (new_msg->msg == NULL) {
        return;
    }
    new_msg->msg[0] = malloc(sizeof(uint8_t) * 2);
    if (new_msg->msg[0] == NULL) {
        return;
    }
    new_msg->msg[0][0] = '\0';
    new_msg->msg[0] = (uint8_t *)strcat((char *)new_msg->msg[0], "ko");
}

static int to_check_ressources(ia_t *ia, common_t *com)
{
    if (ia->player->level == 1) {
        if (com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] > 0) {
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] -= 1;
            return 0;
        }
    }
    if (ia->player->level == 2) {
        if (com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] > 0 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[2] > 0 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] > 0) {
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] -= 1;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[2] -= 1;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] -= 1;
            return 0;
        }
    }
    if (ia->player->level == 3) {
        if (com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] > 1 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] > 0 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[5] > 1) {
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] -= 2;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] -= 1;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[5] -= 2;
            return 0;
        }
    }
    if (ia->player->level == 4) {
        if (com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] > 0 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[2] > 0 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] > 1 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[5] > 0) {
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] -= 1;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[2] -= 1;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] -= 2;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[5] -= 1;
            return 0;
        }
    }
    if (ia->player->level == 5) {
        if (com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] > 0 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[2] > 1 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] > 0 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[4] > 2) {
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] -= 1;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[2] -= 2;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] -= 1;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[4] -= 3;
            return 0;
        }
    }
    if (ia->player->level == 6) {
        if (com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] > 0 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[2] > 1 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] > 2 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[5] > 0) {
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] -= 1;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[2] -= 2;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] -= 3;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[5] -= 1;
            return 0;
        }
    }
    if (ia->player->level == 7) {
        if (com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] > 1 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[2] > 1 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] > 1 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[4] > 1 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[5] > 1 &&
        com->gui->map.tiles[ia->player->x][ia->player->y].ressources[6] > 0) {
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[1] -= 2;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[2] -= 2;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[3] -= 2;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[4] -= 2;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[5] -= 2;
            com->gui->map.tiles[ia->player->x][ia->player->y].ressources[6] -= 1;
            return 0;
        }
    }
    return -1;
}

static void to_complete_ia_in_incantation(int nbr_ia, u_int8_t **arg, tile_t *tile)
{
    if (nbr_ia == 1) {
        tile->nb_player_incantations = realloc(tile->nb_player_incantations, sizeof(size_t) * 1);
        if (tile->nb_player_incantations == NULL) {
            return;
        }
        tile->nb_player_incantations[0] = atoi((char *)arg[3]);
    }
    if (nbr_ia == 2) {
        tile->nb_player_incantations = realloc(tile->nb_player_incantations, sizeof(size_t) * 2);
        if (tile->nb_player_incantations == NULL) {
            return;
        }
        tile->nb_player_incantations[0] = atoi((char *)arg[3]);
        tile->nb_player_incantations[0] = atoi((char *)arg[4]);
    }
    if (nbr_ia == 4) {
        tile->nb_player_incantations = realloc(tile->nb_player_incantations, sizeof(size_t) * 4);
        if (tile->nb_player_incantations == NULL) {
            return;
        }
        tile->nb_player_incantations[0] = atoi((char *)arg[3]);
        tile->nb_player_incantations[0] = atoi((char *)arg[4]);
        tile->nb_player_incantations[0] = atoi((char *)arg[5]);
        tile->nb_player_incantations[0] = atoi((char *)arg[6]);
    }
    if (nbr_ia == 6) {
        tile->nb_player_incantations = realloc(tile->nb_player_incantations, sizeof(size_t) * 6);
        if (tile->nb_player_incantations == NULL) {
            return;
        }
        tile->nb_player_incantations[0] = atoi((char *)arg[3]);
        tile->nb_player_incantations[0] = atoi((char *)arg[4]);
        tile->nb_player_incantations[0] = atoi((char *)arg[5]);
        tile->nb_player_incantations[0] = atoi((char *)arg[6]);
        tile->nb_player_incantations[0] = atoi((char *)arg[7]);
        tile->nb_player_incantations[0] = atoi((char *)arg[8]);
    }
}

static void call_function_gui(ia_t *ia, common_t *com, msg_queue_t *new_msg)
{
    u_int8_t **arg;
    int result_ia = 0;
    char buffer_player[256];

    if (ia->player->level == 1) {
        if (to_check_ressources(ia, com) == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg = malloc(sizeof(u_int8_t *) * 4);
        if (arg == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", ia->player->x);
        arg[0] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[0] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[0][0] = '\0';
        strcat((char*)arg[0], buffer_player);
        sprintf(buffer_player, "%d", ia->player->y);
        arg[1] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[1] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[1][0] = '\0';
        strcat((char*)arg[1], buffer_player);
        sprintf(buffer_player, "%ld", ia->player->level);
        arg[2] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[2] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[2][0] = '\0';
        strcat((char*)arg[2], buffer_player);
        sprintf(buffer_player, "%d", ia->player->id);
        arg[3] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[3] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[3][0] = '\0';
        strcat((char*)arg[3], buffer_player);
        to_complete_ia_in_incantation(1, arg, &com->gui->map.tiles[ia->player->x][ia->player->y]);
        funct_server_pic(arg, com->gui, com);
        free_arg(4, arg);
    } else if (ia->player->level == 2 || ia->player->level == 3) {
        arg = malloc(sizeof(u_int8_t *) * 5);
        if (arg == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", ia->player->x);
        arg[0] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[0] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[0][0] = '\0';
        strcat((char*)arg[0], buffer_player);
        sprintf(buffer_player, "%d", ia->player->y);
        arg[1] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[1] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[1][0] = '\0';
        strcat((char*)arg[1], buffer_player);
        sprintf(buffer_player, "%ld", ia->player->level);
        arg[2] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[2] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[2][0] = '\0';
        strcat((char*)arg[2], buffer_player);
        sprintf(buffer_player, "%d", ia->player->id);
        arg[3] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[3] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[3][0] = '\0';
        strcat((char*)arg[3], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[4] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[4] == NULL) {
        }
        arg[4][0] = '\0';
        strcat((char*)arg[4], buffer_player);
        to_complete_ia_in_incantation(2, arg, &com->gui->map.tiles[ia->player->x][ia->player->y]);
        funct_server_pic(arg, com->gui, com);
        free_arg(5, arg);
    } else if (ia->player->level == 4 || ia->player->level == 5) {
        arg = malloc(sizeof(u_int8_t *) * 7);
        if (arg == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", ia->player->x);
        arg[0] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[0] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[0][0] = '\0';
        strcat((char*)arg[0], buffer_player);
        sprintf(buffer_player, "%d", ia->player->y);
        arg[1] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[1] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[1][0] = '\0';
        strcat((char*)arg[1], buffer_player);
        sprintf(buffer_player, "%ld", ia->player->level);
        arg[2] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[2] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[2][0] = '\0';
        strcat((char*)arg[2], buffer_player);
        sprintf(buffer_player, "%d", ia->player->id);
        arg[3] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[3] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[3][0] = '\0';
        strcat((char*)arg[3], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[4] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[4] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[4][0] = '\0';
        strcat((char*)arg[4], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[5] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[5] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[5][0] = '\0';
        strcat((char*)arg[5], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[6] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[6] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[6][0] = '\0';
        strcat((char*)arg[6], buffer_player);
        to_complete_ia_in_incantation(4, arg, &com->gui->map.tiles[ia->player->x][ia->player->y]);
        funct_server_pic(arg, com->gui, com);
        free_arg(7, arg);
    } else {
        arg = malloc(sizeof(u_int8_t *) * 9);
        if (arg == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", ia->player->x);
        arg[0] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[0] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[0][0] = '\0';
        strcat((char*)arg[0], buffer_player);
        sprintf(buffer_player, "%d", ia->player->y);
        arg[1] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[1] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[1][0] = '\0';
        strcat((char*)arg[1], buffer_player);
        sprintf(buffer_player, "%ld", ia->player->level);
        arg[2] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[2] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[2][0] = '\0';
        strcat((char*)arg[2], buffer_player);
        sprintf(buffer_player, "%d", ia->player->id);
        arg[3] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[3] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[3][0] = '\0';
        strcat((char*)arg[3], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[4] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[4] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[4][0] = '\0';
        strcat((char*)arg[4], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[5] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[5] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[5][0] = '\0';
        strcat((char*)arg[5], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[6] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[6] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[6][0] = '\0';
        strcat((char*)arg[6], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[7] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[7] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[7][0] = '\0';
        strcat((char*)arg[7], buffer_player);
        result_ia = to_find_ia_incantation(com, ia);
        if (result_ia == -1) {
            to_create_message_response_ia(new_msg);
            return;
        }
        sprintf(buffer_player, "%d", result_ia);
        arg[8] = malloc(sizeof(u_int8_t) * strlen(buffer_player));
        if (arg[8] == NULL) {
            to_create_message_response_ia(new_msg);
            return;
        }
        arg[8][0] = '\0';
        strcat((char*)arg[8], buffer_player);
        to_complete_ia_in_incantation(6, arg, &com->gui->map.tiles[ia->player->x][ia->player->y]);
        funct_server_pic(arg, com->gui, com);
        free_arg(9, arg);
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
    if (ia->player->incantation == NO) {
        call_function_gui(ia, com, new_msg);
    } else {
        to_create_message_response_ia(new_msg);
    }
    new_msg->time = 300 / com->freq;
    new_msg->start = 0;
    new_msg->msg = NULL;
    new_msg->handler = &funct_response_ia_incantation;
    new_msg->next_msg = ia->msg_queue;
    ia->msg_queue = new_msg;
    basic_log("rentrer dans la funct_client_ia_incantation", CYAN, 0);
}
