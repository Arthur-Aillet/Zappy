/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_bct
*/

#include "zappy.h"

/**
 @brief retrieve the number of resources according to
 their type on the tile
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param gui_t *gui: common structure of all server data
 @param size_t x: position x on the tiles
 @param size_t y: position y on the tiles
 @param char *buf_x: receives the new argument to be put
 in the response to the gui
 @return void
**/
static void funct_ressources_on_tiles(gui_t *gui, size_t x,
                                        size_t y, char *buf_x)
{
    for (int i = 0; i < 7; i++) {
        sprintf(buf_x, "%ld", gui->map.tiles[y][x].ressources[i]);
        GUI_SIZE += strlen(buf_x) + 3;
        GUI_OCTETS = realloc(GUI_OCTETS, sizeof(char) * (GUI_SIZE));
        if (GUI_OCTETS == NULL) {
            return;
        }
        strcat(GUI_OCTETS, " ");
        strcat(GUI_OCTETS, buf_x);
    }
    strcat(GUI_OCTETS, "\n");
}

/**
 @brief prepare the message for the reply to the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param gui_t *gui: common structure of all server data
 @param char *buf_x: position x on the tiles
 @param char *buf_y: position y on the tiles
 @return void
**/
static void funct_post_tiles(char *buf_x, char *buf_y, gui_t *gui)
{
    GUI_SIZE += 7 + strlen(buf_x) + strlen(buf_y);
    GUI_OCTETS = realloc(GUI_OCTETS, sizeof(char) * (GUI_SIZE));
    if (GUI_OCTETS == NULL) {
        return;
    }
    strcat(GUI_OCTETS, "bct");
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, buf_x);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, buf_y);
}

/**
 @brief prepare response for the gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param gui_t *gui: common structure of all server data
 @param size_t x: position x on the tiles
 @param size_t y: position y on the tiles
 @return void
**/
void funct_prepare_response(gui_t *gui, size_t x, size_t y)
{
    char buf_y[256];
    char buf_x[256];

    sprintf(buf_x, "%ld", x);
    sprintf(buf_y, "%ld", y);
    funct_post_tiles(buf_x, buf_y, gui);
    funct_ressources_on_tiles(gui, x, y, buf_x);
}

/**
 @brief bct command response to gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the gui structure
 @return void
**/
void funct_server_bct(char **args, void *info, common_t *common)
{
    (void)common;
    gui_t *gui = (gui_t *)info;

    if (args == NULL || args[0] == NULL || args[1] == NULL) {
        error("Invalid arguments", 0);
        return;
    }
    GUI_SIZE = 6 + strlen(args[0]) + strlen(args[1]);
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    funct_prepare_response(gui, atoi(args[0]), atoi(args[1]));
    write(gui->buffer.sock.sockfd, GUI_OCTETS, strlen(GUI_OCTETS));
    free(GUI_OCTETS);
}
