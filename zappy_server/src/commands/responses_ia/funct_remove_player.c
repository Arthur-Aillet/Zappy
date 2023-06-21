/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_remove_player
*/

#include "zappy.h"

static void remove_finish_choose_player(player_t *ennemy, player_t *ia,
                                        common_t *com)
{
    if (ia->orientation == Sud) {
        if (ennemy->x == 0) {
            ennemy->x = com->gui->map.height;
        } else {
            ennemy->x -= 1;
        }
    } else {
        if ((size_t)ennemy->y == com->gui->map.width) {
            ennemy->y = 0;
        } else {
            ennemy->y += 1;
        }
    }
}

static void remove_choose_player_est(player_t *ennemy, common_t *com)
{
    if (ennemy->y == 0) {
        ennemy->y = com->gui->map.width;
    } else {
        ennemy->y -= 1;
    }
}

static void remove_choose_player(player_t *ennemy, common_t *com,
                                uint8_t **args, player_t *ia)
{
    if (ia->orientation == North) {
        if ((size_t)ennemy->x == com->gui->map.height) {
            ennemy->x = 0;
        } else {
            ennemy->x += 1;
        }
    } else if (ia->orientation == Est) {
        remove_choose_player_est(ennemy, com);
    } else {
        remove_finish_choose_player(ennemy, ia, com);
    }
    funct_server_pex(args, com->gui, com);
}

static int set_nbr_ia(ia_t *ia)
{
    if (ia->player->level == 1) {
        return 1;
    }
    if (ia->player->level == 2 || ia->player->level == 3) {
        return 2;
    }
    if (ia->player->level == 4 || ia->player->level == 5) {
        return 4;
    }
    return 6;
}

static void funct_prepare_response_gui(player_t *ia, common_t *com, int r)
{
    u_int8_t **args = malloc(sizeof(u_int8_t *) * 3);
    char buffer_args[256];

    if (args == NULL) {
        return;
    }
    sprintf(buffer_args, "%d", ia->x);
    args[0] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (args[0] == NULL) {
        return;
    }
    args[0][0] = '\0';
    strcat((char*)args[0], buffer_args);
    sprintf(buffer_args, "%d", ia->y);
    args[1] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (args[1] == NULL) {
        return;
    }
    args[1][0] = '\0';
    strcat((char*)args[1], buffer_args);
    sprintf(buffer_args, "%d", r);
    args[1] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (args[1] == NULL) {
        return;
    }
    args[1][0] = '\0';
    strcat((char*)args[1], buffer_args);
    funct_server_pie(args, com->gui, com);
}

static void free_msg_queue(msg_queue_t msg)
{
    for (int i = 0; msg.msg[i]; i++) {
        free(msg.msg[i]);
    }
    free(msg.msg);
}

static void to_check_status_incantation(common_t *com, player_t *ia)
{
    int i = set_nbr_ia(to_find_ia_int(com->gui->map.tiles[ia->x][ia->y].nb_player_incantations[0], com));
    int cmp = 0;
    ia_t *ia_tmp;
    u_int8_t **args = malloc(sizeof(u_int8_t *) * 1);

    if (args == NULL) {
        return;
    }
    args[0] = malloc(sizeof(u_int8_t) * 2);
    if (args[0] == NULL) {
        return;
    }
    args[0][0] = '\0';
    args[0] = (u_int8_t *)strcat((char *)args[0], "ko");
    for (int tmp = 0; tmp < i; tmp++) {
        ia_tmp = to_find_ia_int(com->gui->map.tiles[ia->x][ia->y].nb_player_incantations[tmp], com);
        if (ia_tmp->player->incantation == MASTER) {
            for (cmp = 0; ia_tmp->msg_queue[cmp].next_msg != NULL; cmp++);
            free_msg_queue(ia_tmp->msg_queue[cmp]);
            ia_tmp->msg_queue[cmp - 1].next_msg = NULL;
            funct_response_ia_incantation(args, com->gui, com);
        }
        ia_tmp->player->incantation = NO;
    }
    funct_prepare_response_gui(ia, com, 0);
}

void remove_player(player_t *ennemy, player_t *ia, common_t *com)
{
    uint8_t **args = malloc(sizeof(uint8_t *) * 1);
    char buffer_ennemy[256];

    if (args == NULL) {
        return;
    }
    if (ennemy->incantation != NO) {
        to_check_status_incantation(com, ia);
    }
    sprintf(buffer_ennemy, "%d", ennemy->id);
    args[0] = malloc(sizeof(uint8_t) * strlen(buffer_ennemy));
    if (args[0] == NULL) {
        return;
    }
    args[0][0] = '\0';
    strcat((char*)args[0], buffer_ennemy);
    remove_choose_player(ennemy, com, args, ia);
}
