/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pie
*/

#include "zappy.h"

/**
 @brief pie command response to gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the gui structure
 @return void
**/
void funct_server_pie(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;

    (void)common;
    GUI_SIZE = strlen(args[0]) + strlen(args[1]) + strlen(args[2]) + 8;
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    sprintf(GUI_OCTETS, "pie %s %s %s\n", args[0], args[1], args[2]);
    write(gui->buffer.sock.sockfd, GUI_OCTETS, strlen(GUI_OCTETS));
    basic_log("pie send", C, 0);
}
