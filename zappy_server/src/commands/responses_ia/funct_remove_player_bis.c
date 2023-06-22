/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_remove_player_bis
*/

#include "zappy.h"

static void remove_finish_choose_player(player_t *ennemy, player_t *ia,
                                        common_t *com)
{
    if (ia->orientation == Sud) {
        if (ennemy->y == 0) {
            ennemy->y = com->gui->map.height;
        } else {
            ennemy->y -= 1;
        }
    } else {
        if ((size_t)ennemy->x == com->gui->map.width) {
            ennemy->x = 0;
        } else {
            ennemy->x += 1;
        }
    }
}

static void remove_choose_player_est(player_t *ennemy, common_t *com)
{
    if (ennemy->x == 0) {
        ennemy->x = com->gui->map.width;
    } else {
        ennemy->x -= 1;
    }
}

void remove_choose_player(player_t *ennemy, common_t *com,
                                uint8_t **args, player_t *ia)
{
    if (ia->orientation == North) {
        if ((size_t)ennemy->y == com->gui->map.height) {
            ennemy->y = 0;
        } else {
            ennemy->y += 1;
        }
    } else if (ia->orientation == Est) {
        remove_choose_player_est(ennemy, com);
    } else {
        remove_finish_choose_player(ennemy, ia, com);
    }
    funct_server_pex(args, com->gui, com);
}

int set_nbr_ia(ia_t *ia)
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

u_int8_t *prepare_arg_response_gui(int x)
{
    char buffer_args[256];
    u_int8_t *args;

    sprintf(buffer_args, "%d", x);
    args = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (args == NULL) {
        return NULL;
    }
    args[0] = '\0';
    args = (u_int8_t*)strcat((char*)args, buffer_args);
    return args;
}
