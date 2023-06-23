/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_sst
*/

#include "zappy.h"
#include <string.h>

void funct_server_sst(char **args, void *info, common_t *com)
{
    gui_t *gui = (gui_t *)info;

    GUI_SIZE += 6;
    GUI_OCTETS = realloc(GUI_OCTETS,
                sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    com->freq = atoi(args[0]);
    GUI_OCTETS[0] = '\0';
    sprintf(GUI_OCTETS, "sst %s\n", args[0]);
    write(gui->buffer.sock.sockfd, GUI_OCTETS,
        strlen(GUI_OCTETS));
    printf("rentrer dans la fonctions funct_server_sst\n");
}
