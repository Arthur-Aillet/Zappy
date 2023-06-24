/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_plv
*/

#include "zappy.h"
#include <string.h>
#include <stdlib.h>

static void funct_prepare_res(gui_t *gui, ia_t *tmp_ia, char **args)
{
    char str_level[3];

    sprintf(str_level, "%ld", tmp_ia->player->level);
    GUI_SIZE += (strlen(str_level) + 7);
    GUI_OCTETS = realloc(GUI_OCTETS,
                sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    sprintf(GUI_OCTETS, "plv %s %s\n",
                                    args[0], str_level);
}

void funct_server_plv(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);

    if (tmp_ia == NULL) {
        return;
    }
    funct_prepare_res(gui, tmp_ia, args);
    write(gui->buffer.sock.sockfd, GUI_OCTETS,
        strlen(GUI_OCTETS));
    printf("rentrer dans la fonctions funct_server_plv\n");
}
