/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pnw
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
static void funct_prepare_res(gui_t *gui, char **args)
{
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    sprintf(GUI_OCTETS, "pnw #%s %s %s %s %s %s\n",
    args[0], args[1],args[2], args[3], args[4], args[5]);
}

/**
 @brief pnw command response to gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the gui structure
 @return void
**/
void funct_server_pnw(char **args, void *info, common_t *common)
{
    (void)common;
    gui_t *gui = (gui_t *)info;

    GUI_SIZE = strlen(args[0]) +
    strlen(args[1]) + strlen(args[2]) + strlen(args[3]) +
    strlen(args[4]) + strlen(args[5]) + 12;
    funct_prepare_res(gui, args);
    GUI_SIZE = strlen(GUI_OCTETS);
    write(gui->buffer.sock.sockfd, GUI_OCTETS, GUI_SIZE);
    basic_log("Send pnw", C, 0);
    free(GUI_OCTETS);
}
