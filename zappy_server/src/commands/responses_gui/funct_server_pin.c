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
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize - 2] = '\n';
    gui->buffer.bufferWrite.usedSize += 1;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                    sizeof(uint8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
}

static void funct_ressource_in_ia(gui_t *gui, ia_t *ia)
{
    char str_ressource[20];

    for (int i = 0; i < 7; i++) {
        sprintf(str_ressource, "%ld", ia->player->inventory[i]);
        gui->buffer.bufferWrite.usedSize += strlen(str_ressource) + 1;
        gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets
        , sizeof(uint8_t) * (gui->buffer.bufferWrite.usedSize));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char*)gui->buffer.bufferWrite.octets, str_ressource);
        strcat((char*)gui->buffer.bufferWrite.octets, " ");
    }
    funct_finish_response(gui);
}

static void funct_prepare_res(gui_t *gui, ia_t *ia)
{
    char buffer[1024];
    sprintf(buffer, "%d%d%d", ia->player->id, ia->player->x, ia->player->y);
    gui->buffer.bufferWrite.usedSize = 8 + strlen(buffer);
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                        sizeof(uint8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    sprintf((char*)gui->buffer.bufferWrite.octets, "pin %d %d %d ",
                    ia->player->id, ia->player->x, ia->player->y);
    funct_ressource_in_ia(gui, ia);
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize - 1] = '\0';
}

void funct_server_pin(uint8_t **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *ia = to_find_ia(args[0], common);

    if (ia == NULL) {
        return;
    }
    funct_prepare_res(gui, ia);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pin\n");
}
