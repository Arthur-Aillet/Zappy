/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_sgt
*/

#include "zappy.h"
#include <string.h>
#include <stdlib.h>

void funct_server_sgt(char **args, void *info, common_t *common)
{
    (void)args;
    gui_t *gui = (gui_t *)info;
    char str_freq[20];

    sprintf(str_freq, "%ld", common->freq);
    GUI_SIZE = strlen(str_freq) + 6;
    GUI_OCTETS = realloc(GUI_OCTETS,
                sizeof(char) * (GUI_SIZE + 1));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    strcat(GUI_OCTETS, "sgt ");
    strcat(GUI_OCTETS, str_freq);
    strcat(GUI_OCTETS, "\n\0");
    write(gui->buffer.sock.sockfd, GUI_OCTETS,
        GUI_SIZE);
    printf("rentrer dans la fonctions funct_server_sgt\n");
}
