/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pnw
*/

#include "zappy.h"
#include <string.h>

static void funct_prepare_res(gui_t *gui, char **args)
{
    free(GUI_OCTETS);
    GUI_OCTETS = malloc(sizeof(char) *
    (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "pnw #");
    strcat(GUI_OCTETS, args[0]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[1]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[2]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[3]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[4]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[5]);
    strcat(GUI_OCTETS, "\n\0");
}

void funct_server_pnw(char **args, void *info, common_t *common)
{
    (void)common;
    gui_t *gui = (gui_t *)info;

    GUI_SIZE = strlen(args[0]) +
    strlen(args[1]) + strlen(args[2]) + strlen(args[3]) +
    strlen(args[4]) + strlen(args[5]) + 12;
    funct_prepare_res(gui, args);
    GUI_SIZE =
    strlen(GUI_OCTETS);
    write(gui->buffer.sock.sockfd, GUI_OCTETS,
        GUI_SIZE);
    basic_log("Send pnw command tout the GUI", C, 0);
}
