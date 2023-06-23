/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pie
*/

#include "zappy.h"

void funct_server_pie(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;

    (void)common;
    GUI_SIZE = strlen(args[0]) +
                    strlen(args[1]) + strlen(args[2]) + 8;
    GUI_OCTETS = realloc(GUI_OCTETS,
                sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "pie ");
    strcat(GUI_OCTETS, args[0]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[1]);
    strcat(GUI_OCTETS, " ");
    strcat(GUI_OCTETS, args[2]);
    strcat(GUI_OCTETS, "\n\0");
    write(gui->buffer.sock.sockfd, GUI_OCTETS,
        GUI_SIZE);
    printf("rentrer dans la fonctions funct_server_pie\n");
}
