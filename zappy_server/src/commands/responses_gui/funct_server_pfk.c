/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pfk
*/

#include "zappy.h"

/**
 @brief prepare response for the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param gui_t *gui: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @return void
**/
static void funct_prepare_res(gui_t *gui, char **args)
{
    GUI_SIZE = strlen(args[0]) + 6;
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "pfk ");
    strcat(GUI_OCTETS, args[0]);
    strcat(GUI_OCTETS, "\n\0");
}

/**
 @brief pfk command response to gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the gui structure
 @return void
**/
void funct_server_pfk(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);
    team_t *tmp_team;

    if (tmp_ia == NULL) {
        return;
    }
    tmp_team = to_find_team_by_uint8_t(args[0], common);
    if (tmp_team == NULL) {
        return;
    }
    funct_prepare_res(gui, args);
    write(gui->buffer.sock.sockfd, GUI_OCTETS, GUI_SIZE);
    free(GUI_OCTETS);
}
