/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_remove_player
*/

#include "zappy.h"

static void funct_prepare_response_gui(player_t *ia,
                                    common_t *com, int r)
{
    u_int8_t **args = malloc(sizeof(u_int8_t *) * 3);

    if (args == NULL) {
        return;
    }
    args[0] = prepare_arg_response_gui(ia->x);
    args[1] = prepare_arg_response_gui(ia->y);
    args[2] = prepare_arg_response_gui(r);
    funct_server_pie(args, com->gui, com);
}

static int funct_status_master(ia_t *ia_tmp)
{
    int cmp;

    for (cmp = 0; ia_tmp->msg_queue[cmp].next_msg != NULL; cmp++);
    return cmp;
}

static void funct_status_incantation(int i, common_t *com,
                                player_t *ia, u_int8_t **args)
{
    ia_t *ia_tmp;
    int cmp = 0;

    for (int tmp = 0; tmp < i; tmp++) {
        ia_tmp = to_find_ia_int(com->gui->map.tiles[ia->x][ia->y].
        nb_player_incantations[tmp], com);
        if (ia_tmp->player->incantation == MASTER) {
            cmp = funct_status_master(ia_tmp);
            free_msg_queue(ia_tmp->msg_queue[cmp]);
            ia_tmp->msg_queue[cmp - 1].next_msg = NULL;
            funct_response_ia_incantation(args, com->gui, com);
        }
        ia_tmp->player->incantation = NO;
    }
}

static void to_check_status_incantation(common_t *com, player_t *ia)
{
    int i = set_nbr_ia(to_find_ia_int(com->gui->map.tiles
    [ia->x][ia->y].nb_player_incantations[0], com));
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
    funct_status_incantation(i, com, ia, args);
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
