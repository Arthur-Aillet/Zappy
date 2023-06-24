/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_ppo
*/

#include "zappy.h"
#include <string.h>

static void funct_prepare_res(gui_t *gui, char **args, ia_t *tmp_ia)
{
    char buffer_x[256];
    char buffer_y[256];
    char buffer_o[256];

    sprintf(buffer_x, "%d", tmp_ia->player->x);
    sprintf(buffer_y, "%d", tmp_ia->player->y);
    sprintf(buffer_o, "%ld", tmp_ia->player->orientation);
    GUI_SIZE += (strlen(buffer_x) + strlen(buffer_y)
    + strlen(buffer_o) + 9);
    GUI_OCTETS = realloc(GUI_OCTETS,
    sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    sprintf(GUI_OCTETS, "ppo %s %s %s %s\n",
            args[0], buffer_x, buffer_y, buffer_o);
}

void funct_server_ppo(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);

    if (tmp_ia == NULL) {
        return;
    }
    funct_prepare_res(gui, args, tmp_ia);
    printf("%s\n", GUI_OCTETS);
    write(gui->buffer.sock.sockfd, GUI_OCTETS,
        strlen(GUI_OCTETS));
    printf("rentrer dans la fonctions funct_server_ppo\n");
}
