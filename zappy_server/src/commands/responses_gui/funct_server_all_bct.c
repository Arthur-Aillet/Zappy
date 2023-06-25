/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_all_bct
*/

#include "zappy.h"

static void funct_for_on_tiles(gui_t *gui)
{
    for (size_t nbr_tiles_height = 0; nbr_tiles_height < gui->map.height;
                                        nbr_tiles_height++) {
        for (size_t nbr_tiles_width = 0; nbr_tiles_width < gui->map.width;
                                        nbr_tiles_width++) {
            funct_prepare_response(gui, nbr_tiles_width, nbr_tiles_height);
        }
    }
}

void funct_server_all_bct(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;

    (void)common;
    (void)args;
    GUI_SIZE = 1;
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    funct_for_on_tiles(gui);
    GUI_OCTETS[GUI_SIZE - 1] = '\0';
    write(gui->buffer.sock.sockfd, GUI_OCTETS, strlen(GUI_OCTETS));
    free(GUI_OCTETS);
}
