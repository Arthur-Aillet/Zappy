/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_clientèia_incantation_bis
*/

#include "zappy.h"

static int to_find_ia_incantation_bis(common_t *com, ia_t *ia, team_t *team)
{
    for (size_t tmp = 0; tmp < com->nb_ia; tmp++) {
        if (ia->player->x == com->ia[tmp].player->x && ia->player->y ==
        com->ia[tmp].player->y && ia->player->level ==
        com->ia[tmp].player->level && ia->player->id != com->ia[tmp].player->id
        && team->players[tmp].incantation == NO) {
            com->ia[tmp].player->incantation = FOLLOWER;
            return com->ia[tmp].player->id;
        }
    }
    return -1;
}

int to_find_ia_incantation(common_t *com, ia_t *ia)
{
    team_t *team = to_find_team_by_int(ia->player->id, com);

    for (size_t tmp = 0; tmp < team->actif_player; tmp++) {
        if (ia->player->x == team->players[tmp].x && ia->player->y ==
        team->players[tmp].y && ia->player->level == team->players[tmp].level
        && ia->player->id != team->players[tmp].id &&
        team->players[tmp].incantation == NO) {
            team->players[tmp].incantation = FOLLOWER;
            return team->players[tmp].id;
        }
    }
    return to_find_ia_incantation_bis(com, ia, team);
}

void to_create_message_response_ia(msg_queue_t *new_msg)
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

int to_check_ressources(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 1) {
        if (com->gui->map.tiles[x][y].ressources[1] > 0) {
            com->gui->map.tiles[x][y].ressources[1] -= 1;
            com->gui->map.density -= 1;
            return 0;
        }
    }
    if (ia->player->level == 2) {
        if (com->gui->map.tiles[x][y].ressources[1] > 0 &&
        com->gui->map.tiles[x][y].ressources[2] > 0 &&
        com->gui->map.tiles[x][y].ressources[3] > 0) {
            com->gui->map.tiles[x][y].ressources[1] -= 1;
            com->gui->map.tiles[x][y].ressources[2] -= 1;
            com->gui->map.tiles[x][y].ressources[3] -= 1;
            com->gui->map.density -= 3;
            return 0;
        }
    }
    return to_check_ressources_bis(ia, com, x, y);
}

void to_complete_ia_in_incantation_bis(int nbr_ia,
                                u_int8_t **arg, tile_t *tile)
{
    if (nbr_ia == 2) {
        tile->nb_player_incantations =
        realloc(tile->nb_player_incantations, sizeof(size_t) * 2);
        if (tile->nb_player_incantations == NULL) {
            return;
        }
        tile->nb_player_incantations[0] = atoi((char *)arg[3]);
        tile->nb_player_incantations[0] = atoi((char *)arg[4]);
    }
    if (nbr_ia == 4) {
        tile->nb_player_incantations =
        realloc(tile->nb_player_incantations, sizeof(size_t) * 4);
        tile->nb_player_incantations[0] = atoi((char *)arg[3]);
        tile->nb_player_incantations[0] = atoi((char *)arg[4]);
        tile->nb_player_incantations[0] = atoi((char *)arg[5]);
        tile->nb_player_incantations[0] = atoi((char *)arg[6]);
    }
}
