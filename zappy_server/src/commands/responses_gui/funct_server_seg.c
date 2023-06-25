/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_seg
*/

#include "zappy.h"
#include <string.h>

/**
 @brief prepare response for the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param gui_t *gui: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @return void
**/
static void funct_prepare_res(gui_t *gui, common_t *common,
                                team_t *tmp_team, char **args)
{
    GUI_SIZE = strlen(tmp_team->name) + 6;
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    common->freq = atoi(args[0]);
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "seg ");
    strcat(GUI_OCTETS, tmp_team->name);
    strcat(GUI_OCTETS, "\n\0");
}

/**
 @brief check the level of the players in the team to know if it won or not
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param gui_t *gui: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @return void
**/
static int to_check_in(team_t *tmp_team)
{
    int cmp = 0;

    for (size_t i = 0; i < tmp_team->actif_player; i++) {
        if (tmp_team->players[i].level == 8) {
            cmp++;
        }
    }
    if (cmp >= 6) {
        return 0;
    }
    return 1;
}

/**
 @brief seg command response to gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the gui structure
 @return void
**/
void funct_server_seg(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    team_t *tmp_team = to_find_team_by_int(ia->player->id, com);

    if (tmp_team == NULL) {
        return;
    }
    if (to_check_in(tmp_team) == 1) {
        return;
    }
    funct_prepare_res(com->gui, com, tmp_team, args);
    write(com->gui->buffer.sock.sockfd, com->GUI_OCTETS, com->GUI_SIZE);
    basic_log("seg send", C, 0);
    free(com->GUI_OCTETS);
}
