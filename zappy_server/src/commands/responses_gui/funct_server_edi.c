/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_edi
*/

#include "zappy.h"

//appeler si un oeuf est ejecter d'une case

void funct_server_edi(char **args, void *info, common_t *common)
{
    (void)common;
    gui_t *gui = (gui_t *)info;

    GUI_SIZE = strlen(args[0]) + 6;
    GUI_OCTETS = realloc(GUI_OCTETS,
                sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "edi ");
    strcat(GUI_OCTETS, args[0]);
    strcat(GUI_OCTETS, "\n\0");
    write(gui->buffer.sock.sockfd, GUI_OCTETS,
        GUI_SIZE);
    printf("rentrer dans la fonctions funct_server_edi\n");
}
