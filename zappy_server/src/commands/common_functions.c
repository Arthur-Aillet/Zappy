/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** common_functions
*/

#include "zappy.h"

void malloc_nbr_args(msg_queue_t *new_msg, size_t nbr_args)
{
    new_msg->msg = malloc(sizeof(char *) * nbr_args);
    if (new_msg->msg == NULL) {
        return;
    }
}

static team_t *to_find_team_by_uint8_t_bis(size_t i, char *n,
                                            common_t *common)
{
    for (size_t y = 0; y < common->teams[i].actif_player; y++) {
        if (common->teams[i].players[y].x >= 0 &&
        atoi(n) == common->teams[i].players[y].id) {
            return &common->teams[i];
        }
    }
    return NULL;
}

team_t *to_find_team_by_uint8_t(char *n, common_t *common)
{
    team_t *tmp = NULL;

    for (size_t i = 0; i < common->nb_teams; i++) {
        tmp = to_find_team_by_uint8_t_bis(i, n , common);
        if (tmp != NULL) {
            return tmp;
        }
    }
    return NULL;
}

static team_t *to_find_team_by_int_bis(size_t i, int n,
                                            common_t *common)
{
    for (size_t y = 0; y < common->teams[i].actif_player; y++) {
        if (common->teams[i].players[y].x >= 0 &&
            n == common->teams[i].players[y].id) {
            return &common->teams[i];
        }
    }
    return NULL;
}

team_t *to_find_team_by_int(int n, common_t *common)
{
    team_t *tmp = NULL;

    for (size_t i = 0; i < common->nb_teams; i++) {
        tmp = to_find_team_by_int_bis(i, n, common);
        if (tmp != NULL) {
            return tmp;
        }
    }
    return NULL;
}
