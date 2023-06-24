/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pgt
*/

#include "zappy.h"
#include <string.h>

static void funct_prepare_res(gui_t *gui, char **args)
{
    GUI_SIZE += (strlen(args[1]) + 7);
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "pgt ");
    strcat(GUI_OCTETS, args[0]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[1]);
    strcat(GUI_OCTETS, "\n\0");
}

void funct_server_pgt(char **args, void *info, common_t *common)
{
    ia_t *tmp_ia = to_find_ia(args[0], common);
    gui_t *gui = (gui_t *)info;

    if (tmp_ia == NULL) {
        return;
    }
    funct_prepare_res(gui, args);
    write(gui->buffer.sock.sockfd, GUI_OCTETS, strlen(GUI_OCTETS));
    basic_log("pgt send", C, 0);
    free(GUI_OCTETS);
}
