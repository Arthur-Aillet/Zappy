/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_connect_nbr
*/

#include "zappy.h"

/**
 @brief connect nbr command response to gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the ia structure
 @return void
**/
void funct_response_ia_connect_nbr(char **args, void *info, common_t *com)
{
    (void)args;
    ia_t *ia = (ia_t *)info;
    team_t *team = to_find_team_by_int(ia->player->id, com);
    char buffer_nb_slot[256];

    sprintf(buffer_nb_slot, "%ld", (team->nb_slot - team->actif_player));
    SIZE = strlen(buffer_nb_slot) + 2;
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    OCTETS[0] = '\0';
    strcat(OCTETS, buffer_nb_slot);
    strcat(OCTETS, "\n\0");
    write(ia->buffer.sock.sockfd, OCTETS, SIZE);
}
