/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_clientèia_incantation_bis
*/

#include "zappy.h"

/**
 @brief find a ia for the incantation continuation
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure of ia
 @param common_t *com: the arguments receive with the command ia
 @param team_t *team: team where we check the ai
 @return int
**/
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

/**
 @brief find a ia for the incantation
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia : structure of ia
 @param common_t *com: the arguments receive with the command ia
 @return int
**/
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

/**
 @brief create a message for the response ia
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param msg_queue_t new_msg: recording of the new
            order in the pending queue
 @return void
**/
void to_create_message_response_ia(msg_queue_t *new_msg)
{
    new_msg->msg = malloc(sizeof(char *) * 1);
    if (new_msg->msg == NULL) {
        return;
    }
    new_msg->msg[0] = malloc(sizeof(char) * 3);
    if (new_msg->msg[0] == NULL) {
        return;
    }
    new_msg->msg[0][0] = '\0';
    new_msg->msg[0] = strcat(new_msg->msg[0], "ko\0");
}

/**
 @brief check the resources it takes to get to level 1 and 2
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia : structure of ia
 @param common_t *com: the arguments receive with the command ia
 @param int x: position ressources x on the map
 @param int y: position ressources y on the map
 @return int
**/
int to_check_ressources(ia_t *ia, common_t *com, int x, int y)
{
    if (ia->player->level == 1) {
        if (C_RESSOURCES(y, x)[LINEMATE] > 0) {
            update_density(&C_DENSITY[LINEMATE],
                            &C_RESSOURCES(y, x)[LINEMATE], -1);
            return 0;
        }
    }
    if (ia->player->level == 2) {
        if (C_RESSOURCES(y, x)[1] > 0 && C_RESSOURCES(y, x)[2] > 0 &&
            C_RESSOURCES(y, x)[3] > 0) {
            update_density(&C_DENSITY[LINEMATE],
                            &C_RESSOURCES(y, x)[LINEMATE], -1);
            update_density(&C_DENSITY[DERAUMERE],
                            &C_RESSOURCES(y, x)[DERAUMERE], -1);
            update_density(&C_DENSITY[SIBUR], &C_RESSOURCES(y, x)[SIBUR], -1);
            return 0;
        }
    }
    return to_check_ressources_bis(ia, com, x, y);
}

/**
 @brief complete the arguments needed for the incantation
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param tile_t *tile: each box of the maps
 @param char **args: the arguments given as parameters
 with the command sent by the ia
 @param int nbr_ia: numbre ia
 @return void
**/
void to_complete_ia_in_incantation_bis(int nbr_ia,
                                char **arg, tile_t *tile)
{
    if (nbr_ia == 2) {
        tile->nb_player_incantations =
        realloc(tile->nb_player_incantations, sizeof(size_t) * 2);
        if (tile->nb_player_incantations == NULL) {
            return;
        }
        tile->nb_player_incantations[0] = atoi(arg[3]);
        tile->nb_player_incantations[0] = atoi(arg[4]);
    }
    if (nbr_ia == 4) {
        tile->nb_player_incantations =
        realloc(tile->nb_player_incantations, sizeof(size_t) * 4);
        tile->nb_player_incantations[0] = atoi(arg[3]);
        tile->nb_player_incantations[0] = atoi(arg[4]);
        tile->nb_player_incantations[0] = atoi(arg[5]);
        tile->nb_player_incantations[0] = atoi(arg[6]);
    }
}
