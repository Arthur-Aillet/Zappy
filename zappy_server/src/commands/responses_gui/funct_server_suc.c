/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_suc
*/

#include "zappy.h"
#include <string.h>

void funct_server_suc(char **args, void *info, common_t *common)
{
    (void)args;
    (void)common;
    gui_t *gui = (gui_t *)info;

    GUI_SIZE = 5;
    GUI_OCTETS = malloc(sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "suc\n\0");
    write(gui->buffer.sock.sockfd, GUI_OCTETS, GUI_SIZE);
    basic_log("suc send", C, 0);
    free(GUI_OCTETS);
}
