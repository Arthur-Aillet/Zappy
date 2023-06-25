/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_tna
*/

#include "zappy.h"
#include <string.h>

static void funct_prepare_res(gui_t *gui, common_t *com)
{
    GUI_SIZE = 1;
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    for (size_t nbr_teams = 0; nbr_teams < com->nb_teams; nbr_teams++) {
        GUI_SIZE += 5 + strlen(com->teams[nbr_teams].name);
        GUI_OCTETS = realloc(GUI_OCTETS, sizeof(char) * (GUI_SIZE));
        if (GUI_OCTETS == NULL) {
            return;
        }
        strcat(GUI_OCTETS, "tna");
        strcat(GUI_OCTETS, " ");
        strcat(GUI_OCTETS,
                com->teams[nbr_teams].name);
        strcat(GUI_OCTETS, "\n");
    }
    GUI_OCTETS[GUI_SIZE - 1] = '\0';
}

void funct_server_tna(char **args, void *info, common_t *com)
{
    (void)args;
    gui_t *gui = (gui_t *)info;

    funct_prepare_res(gui, com);
    write(gui->buffer.sock.sockfd, GUI_OCTETS, GUI_SIZE);
    basic_log("tna send", C, 0);
    free(GUI_OCTETS);
}
