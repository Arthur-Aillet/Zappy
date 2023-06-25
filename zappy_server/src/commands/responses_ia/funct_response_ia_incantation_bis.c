/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_incantation_bis
*/

#include "zappy.h"

/**
 @brief prepare response for the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: structure ia
 @param int r: number orientation ia
 @param char **args: arguments for the response gui
 @return void
**/
static void funct_prepare_response_gui_next(ia_t *ia, char **args,
                                            common_t *com, int r)
{
    char buffer_args[256];

    sprintf(buffer_args, "%d", ia->player->y);
    args[1] = malloc(sizeof(char) * (strlen(buffer_args) + 1));
    if (args[1] == NULL) {
        return;
    }
    args[1][0] = '\0';
    strcat(args[1], buffer_args);
    sprintf(buffer_args, "%d", r);
    args[2] = malloc(sizeof(char) * (strlen(buffer_args) + 1));
    if (args[2] == NULL) {
        return;
    }
    args[2][0] = '\0';
    strcat(args[2], buffer_args);
    args[3] = NULL;
    funct_server_pie(args, com->gui, com);
}

/**
 @brief prepapre response gui incantation
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: structure ia
 @param int r: number orientation ia
 @return void
**/
void funct_prepare_response_gui_incantation(ia_t *ia, common_t *com, int r)
{
    char **args = malloc(sizeof(char *) * 4);
    char buffer_args[256];

    if (args == NULL) {
        return;
    }
    sprintf(buffer_args, "%d", ia->player->x);
    args[0] = malloc(sizeof(char) * (strlen(buffer_args) + 1));
    if (args[0] == NULL) {
        return;
    }
    args[0][0] = '\0';
    strcat(args[0], buffer_args);
    funct_prepare_response_gui_next(ia, args, com, r);
    free_array((void **)args);
}

/**
 @brief set up data needs for level 1 incantation
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param ia_t *ia: structure ia
 @return void
**/
void funct_level_1(ia_t *ia, common_t *com)
{
    char buffer_incantation[256];

    ia->player->level += 1;
    sprintf(buffer_incantation, "%ld", ia->player->level);
    SIZE = 35 + strlen(buffer_incantation);
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    char level[3];
    sprintf(level, "%ld", ia->player->level);
    OCTETS[0] = '\0';
    strcat(OCTETS, "Elevation underway current level ");
    strcat(OCTETS, level);
    strcat(OCTETS, "\n\0");
    funct_prepare_response_gui_incantation(ia, com, 1);
    funct_server_seg(NULL, ia, com);
}
