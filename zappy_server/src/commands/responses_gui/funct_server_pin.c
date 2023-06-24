/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_pin
*/

#include "zappy.h"
#include <string.h>
#include <stdlib.h>

static void funct_finish_response(gui_t *gui)
{
    GUI_OCTETS[GUI_SIZE - 2] = '\n';
    GUI_SIZE += 1;
    GUI_OCTETS = realloc(GUI_OCTETS,
                    sizeof(char) * (GUI_SIZE));
    if (GUI_OCTETS == NULL) {
        return;
    }
}

static void funct_ressource_in_ia(gui_t *gui, ia_t *ia)
{
    char str_ressource[20];

    for (int i = 0; i < 7; i++) {
        sprintf(str_ressource, "%ld", ia->player->inventory[i]);
        GUI_SIZE += strlen(str_ressource) + 1;
        GUI_OCTETS = realloc(GUI_OCTETS
        , sizeof(char) * (GUI_SIZE));
        if (GUI_OCTETS == NULL) {
            return;
        }
        strcat(GUI_OCTETS, str_ressource);
        strcat(GUI_OCTETS, " ");
    }
    funct_finish_response(gui);
}

static void funct_prepare_res(gui_t *gui, ia_t *ia)
{
    char buffer[1024];
    sprintf(buffer, "%d%d%d", ia->player->id, ia->player->x, ia->player->y);
    GUI_SIZE = 8 + strlen(buffer);
    GUI_OCTETS = realloc(GUI_OCTETS,
                        sizeof(char) * (GUI_SIZE));
    if (GUI_OCTETS == NULL) {
        return;
    }
    GUI_OCTETS[0] = '\0';
    sprintf(GUI_OCTETS, "pin %d %d %d ",
                    ia->player->id, ia->player->x, ia->player->y);
    funct_ressource_in_ia(gui, ia);
    GUI_OCTETS[GUI_SIZE - 1] = '\0';
}

void funct_server_pin(char **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *ia = to_find_ia(args[0], common);

    if (ia == NULL) {
        return;
    }
    funct_prepare_res(gui, ia);
    write(gui->buffer.sock.sockfd, GUI_OCTETS,
        GUI_SIZE);
    printf("rentrer dans la fonctions funct_server_pin\n");
}
