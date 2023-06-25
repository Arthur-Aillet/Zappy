/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_plv
*/

#include "zappy.h"
#include <string.h>
#include <stdlib.h>

/**
 @brief prepare response for the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param gui_t *gui: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param ia_t *tmp_ia: structure ia
 @return void
**/
static void funct_prepare_res(gui_t *gui, ia_t *tmp_ia, char **args)
{
    char str_level[3];

    sprintf(str_level, "%ld", tmp_ia->player->level);
    GUI_SIZE += (strlen(str_level) + 7);
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    sprintf(GUI_OCTETS, "plv %s %s\n", args[0], str_level);
}

/**
 @brief pfk command response to gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the gui structure
 @return void
**/
void funct_server_plv(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);

    if (tmp_ia == NULL) {
        return;
    }
    funct_prepare_res(gui, tmp_ia, args);
    write(gui->buffer.sock.sockfd, GUI_OCTETS, strlen(GUI_OCTETS));
    basic_log("plv send", C, 0);
    free(GUI_OCTETS);
}
