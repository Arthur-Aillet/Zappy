/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_enw
*/

#include "zappy.h"

static void funct_prepare_res(gui_t *gui, char **args,
                                char *buffer_x, char *buffer_y)
{
    GUI_SIZE = strlen(args[0]) +
    strlen(args[1]) + strlen(buffer_x) + strlen(buffer_y) + 9;
    GUI_OCTETS = realloc(GUI_OCTETS,
    sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "enw ");
    strcat(GUI_OCTETS, args[0]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[1]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, buffer_x);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, buffer_y);
    strcat(GUI_OCTETS, "\n\0");
}

void funct_server_enw(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);
    char buffer_x[256];
    char buffer_y[256];

    if (tmp_ia == NULL || gui == NULL) {
        return;
    }
    tmp_ia->player->inventory[EGG] -= 1;
    sprintf(buffer_x, "%d", tmp_ia->player->x);
    sprintf(buffer_y, "%d", tmp_ia->player->y);
    funct_prepare_res(gui, args, buffer_x, buffer_y);
    write(gui->buffer.sock.sockfd, GUI_OCTETS,
        GUI_SIZE);
    printf("rentrer dans la fonctions funct_server_enw\n");
}
