/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_incantation
*/

#include "zappy.h"

/**
 @brief set up data needs for level 6 and 7 incantation next
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: structure ia
 @return void
**/
static void funct_level_other_level_next(ia_t *ia, common_t *com)
{
    char level[3];

    sprintf(level, "%ld", ia->player->level);
    OCTETS[0] = '\0';
    strcat(OCTETS,
    "Elevation underway current level ");
    strcat(OCTETS, level);
    strcat(OCTETS, "\n\0");
    funct_prepare_response_gui_incantation(ia, com, 1);
}

/**
 @brief set up data needs for level 6 and 7 incantation
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: structure ia
 @param int nbr_ia_level: number of i need
 @return void
**/
static void funct_level_other_level(ia_t *ia, common_t *com, int nbr_ia_level)
{
    char buffer_incantation[256];
    ia_t *tmp_ia;

    for (int i = 0; i < nbr_ia_level; i++) {
        tmp_ia = to_find_ia_int(com->gui->map.tiles[ia->player->y]
        [ia->player->x].nb_player_incantations[i], com);
        tmp_ia->player->level += 1;
        funct_server_seg(NULL, tmp_ia, com);
    }
    sprintf(buffer_incantation, "%ld", ia->player->level);
    SIZE = 35 + strlen(buffer_incantation);
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    funct_level_other_level_next(ia, com);
}

/**
 @brief choose the function according to level
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: structure ia
 @return void
**/
static void funct_response_ia_incantation_bis(ia_t *ia, common_t *com)
{
    if (ia->player->level == 2 || ia->player->level == 3) {
            funct_level_other_level(ia, com, 2);
    }
    if (ia->player->level == 4 || ia->player->level == 5) {
        funct_level_other_level(ia, com, 4);
    }
    if (ia->player->level == 6 || ia->player->level == 7) {
        funct_level_other_level(ia, com, 6);
    }
}

/**
 @brief prepapre response for the echec incantation
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: structure ia
 @return void
**/
static void funct_response_echec_incantation(ia_t *ia)
{
    SIZE = 4;
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    OCTETS[0] = '\0';
    strcat(OCTETS, "ko\n\0");
}

/**
 @brief incantation command response to ia
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the ia structure
 @return void
**/
void funct_response_ia_incantation(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    if (args != NULL && args[0] != NULL && strcmp(args[0], "ko") == 0) {
        funct_response_echec_incantation(ia);
    } else {
        if (ia->player->level == 1) {
            funct_level_1(ia, com);
        } else {
            funct_response_ia_incantation_bis(ia, com);
        }
    }
    write(ia->buffer.sock.sockfd, OCTETS, SIZE);
    printf("%sPlayer: %s%d%s level up to %s%ld%s\n", P, R, ia->player->id,
            P, B, ia->player->level, N);
}
