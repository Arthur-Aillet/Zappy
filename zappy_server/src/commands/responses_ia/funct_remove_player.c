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

static void remove_choose_player(player_t *ennemy, common_t *com,
                                u_int8_t **args, player_t *ia)
{
    if (ia->orientation == North) {
        if ((size_t)ennemy->x == com->gui->map.height) {
            ennemy->x = 0;
        } else {
            ennemy->x += 1;
        }
    }
    else if (ia->orientation == Est) {
        if (ennemy->y == 0) {
            ennemy->y = com->gui->map.width;
        } else {
            ennemy->y -= 1;
        }
    } else {
        remove_finish_choose_player(ennemy, ia, com);
    }
    funct_server_pex(args, com->gui, com);
}

void remove_player(player_t *ennemy, player_t *ia, common_t *com)
{
    u_int8_t **args = malloc(sizeof(u_int8_t *) * 1);
    char buffer_ennemy[256];

    if (args == NULL) {
        //error
    }
    sprintf(buffer_ennemy, "%d", ennemy->id);
    args[0] = malloc(sizeof(u_int8_t) * strlen(buffer_ennemy));
    if (args[0] == NULL) {
        //error
    }
    args[0][0] = '\0';
    strcat((char*)args[0], buffer_ennemy);
    remove_choose_player(ennemy, com, args, ia);
}
