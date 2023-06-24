/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pdr
*/

#include "zappy.h"

static void funct_prepare_res(char **args, gui_t *gui)
{
    GUI_SIZE = strlen(args[0]) + strlen(args[1]) + 7;
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "pdr ");
    strcat(GUI_OCTETS, args[0]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[1]);
    strcat(GUI_OCTETS, "\n\0");
}

void funct_server_pdr(char **args, void *info, common_t *common)
{
    ia_t *tmp_ia = to_find_ia(args[0], common);
    gui_t *gui = (gui_t *)info;

    if (tmp_ia == NULL) {
        return;
    }
    funct_prepare_res(args, gui);
    write(gui->buffer.sock.sockfd, GUI_OCTETS, GUI_SIZE);
    free(GUI_OCTETS);
}
