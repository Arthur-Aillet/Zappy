/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_enw
*/

#include "zappy.h"

/**
 @brief prepare the message for the reply to the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param gui_t *gui: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param char *buffer_x: position x on the ia
 @param char *buffer_y: position x on the ia
 @return void
**/
static void funct_prepare_res(gui_t *gui, char **args,
                                char *buffer_x, char *buffer_y)
{
    GUI_SIZE = strlen(args[0]) +
    strlen(args[1]) + strlen(buffer_x) + strlen(buffer_y) + 9;
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    sprintf(GUI_OCTETS, "enw %s %s %s %s\n",
            args[0], args[1], buffer_x, buffer_y);
}

/**
 @brief enw command response to gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the gui structure
 @return void
**/
void funct_server_enw(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *ia = to_find_ia(args[1], common);
    char buffer_x[256];
    char buffer_y[256];

    if (ia == NULL || gui == NULL) {
        return;
    }
    if (ia->player->inventory[EGG] > 0)
        ia->player->inventory[EGG] -= 1;
    sprintf(buffer_x, "%d", ia->player->x);
    sprintf(buffer_y, "%d", ia->player->y);
    funct_prepare_res(gui, args, buffer_x, buffer_y);
    write(gui->buffer.sock.sockfd, GUI_OCTETS, GUI_SIZE);
    free(GUI_OCTETS);
}
