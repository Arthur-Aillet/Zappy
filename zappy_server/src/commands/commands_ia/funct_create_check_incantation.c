/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_create_check_incantation
*/

#include "zappy.h"

void to_complete_ia_in_incantation(int nbr_ia, char **arg, tile_t *tile)
{
    if (nbr_ia == 1) {
        tile->nb_player_incantations =
        realloc(tile->nb_player_incantations, sizeof(size_t) * 1);
        tile->nb_player_incantations[0] = atoi(arg[3]);
    }
    if (nbr_ia == 6) {
        tile->nb_player_incantations =
        realloc(tile->nb_player_incantations, sizeof(size_t) * 6);
        tile->nb_player_incantations[0] = atoi(arg[3]);
        tile->nb_player_incantations[0] = atoi(arg[4]);
        tile->nb_player_incantations[0] = atoi(arg[5]);
        tile->nb_player_incantations[0] = atoi(arg[6]);
        tile->nb_player_incantations[0] = atoi(arg[7]);
        tile->nb_player_incantations[0] = atoi(arg[8]);
    }
    to_complete_ia_in_incantation_bis(nbr_ia, arg, tile);
}

char *create_new_arg(int nbr, msg_queue_t *new_msg)
{
    char buffer_player[256];
    char *arg;

    sprintf(buffer_player, "%d", nbr);
    arg = malloc(sizeof(char) * (strlen(buffer_player) + 1));
    if (arg == NULL) {
        to_create_message_response_ia(new_msg);
        return NULL;
    }
    arg[0] = '\0';
    return strcat(arg, buffer_player);
}

void status_level_one(ia_t *ia, common_t *com, msg_queue_t *new_msg)
{
    char **arg;

    arg = malloc(sizeof(char *) * 4);
    if (arg == NULL) {
        to_create_message_response_ia(new_msg);
        return;
    }
    arg[0] = create_new_arg(ia->player->x, new_msg);
    arg[1] = create_new_arg(ia->player->y, new_msg);
    arg[2] = create_new_arg(ia->player->level, new_msg);
    arg[3] = create_new_arg(ia->player->id, new_msg);
    to_complete_ia_in_incantation(1, arg,
    &com->gui->map.tiles[ia->player->y][ia->player->x]);
    funct_server_pic(arg, com->gui, com);
    free_arg(4, arg);
}

static void status_level_two_tree_next(ia_t *ia,
            common_t *com, msg_queue_t *new_msg, char **arg)
{
    int result_ia = 0;

    result_ia = to_find_ia_incantation(com, ia);
    if (result_ia == -1) {
        to_create_message_response_ia(new_msg);
        return;
    }
    arg[4] = create_new_arg(result_ia, new_msg);
    to_complete_ia_in_incantation(2, arg,
    &com->gui->map.tiles[ia->player->y][ia->player->x]);
    funct_server_pic(arg, com->gui, com);
    free_arg(5, arg);
}

void status_level_two_tree(ia_t *ia,
                                common_t *com, msg_queue_t *new_msg)
{
    char **arg;

    arg = malloc(sizeof(char *) * 5);
    if (arg == NULL) {
        to_create_message_response_ia(new_msg);
        return;
    }
    arg[0] = create_new_arg(ia->player->x, new_msg);
    arg[1] = create_new_arg(ia->player->y, new_msg);
    arg[2] = create_new_arg(ia->player->level, new_msg);
    arg[3] = create_new_arg(ia->player->id, new_msg);
    status_level_two_tree_next(ia, com, new_msg, arg);
}
