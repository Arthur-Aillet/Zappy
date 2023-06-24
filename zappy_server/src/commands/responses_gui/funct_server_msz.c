/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_msz
*/

#include "zappy.h"

static void funct_prepare_res(gui_t *gui)
{
    char buffer_x[256];
    char buffer_y[256];

    sprintf(buffer_x, "%ld", gui->map.width);
    sprintf(buffer_y, "%ld", gui->map.height);
    GUI_SIZE = strlen(buffer_x) + strlen(buffer_y) + 7;
    GUI_OCTETS = realloc(GUI_OCTETS, sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    sprintf(GUI_OCTETS, "msz %s %s\n", buffer_x, buffer_y);
    // strcat(GUI_OCTETS, "msz");
    // strcat(GUI_OCTETS, " ");
    // strcat(GUI_OCTETS, buffer_x);
    // strcat(GUI_OCTETS, " ");
    // strcat(GUI_OCTETS, buffer_y);
    // strcat(GUI_OCTETS, "\n\0");
}

void funct_server_msz(char **args, void *info, common_t *common)
{
    (void)common;
    (void)args;
    gui_t *gui = (gui_t *)info;

    funct_prepare_res(gui);
    write(gui->buffer.sock.sockfd, GUI_OCTETS, strlen(GUI_OCTETS));
    printf("rentrer dans la fonctions funct_server_msz\n");
}
