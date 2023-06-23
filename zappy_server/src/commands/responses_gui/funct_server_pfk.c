/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pfk
*/

#include "zappy.h"

static void funct_prepare_res(gui_t *gui, char **args)
{
    GUI_SIZE = strlen(args[0]) + 6;
    GUI_OCTETS = realloc(GUI_OCTETS,
                    sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "pfk ");
    strcat(GUI_OCTETS, args[0]);
    strcat(GUI_OCTETS, "\n\0");
}

void funct_server_pfk(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);
    team_t *tmp_team;

    if (tmp_ia == NULL) {
        return;
    }
    tmp_team = to_find_team_by_uint8_t(args[0], common);
    if (tmp_team == NULL) {
        return;
    }
    funct_prepare_res(gui, args);
    write(gui->buffer.sock.sockfd, GUI_OCTETS,
            GUI_SIZE);
    printf("rentrer dans la fonctions funct_server_pfk\n");
}
