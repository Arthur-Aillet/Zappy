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
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\n';
    gui->buffer.bufferWrite.usedSize += 1;
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                    sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
}

static void funct_ressource_in_ia(gui_t *gui, ia_t *tmp_ia)
{
    char str_ressource[20];

    for (int i = 0; i < 7; i++) {
        sprintf(str_ressource, "%ld", tmp_ia->player->inventory[i]);
        gui->buffer.bufferWrite.usedSize += strlen(str_ressource) + 1;
        gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets
        , sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
        if (gui->buffer.bufferWrite.octets == NULL) {
            return;
        }
        strcat((char*)gui->buffer.bufferWrite.octets, str_ressource);
        strcat((char*)gui->buffer.bufferWrite.octets, " ");
    }
    funct_finish_response(gui);
}

static void funct_prepare_response(gui_t *gui, ia_t *tmp_ia, uint8_t **args)
{
    gui->buffer.bufferWrite.usedSize = 7 + strlen((char*)args[1]) +
                                    strlen((char*)args[2]);
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
                        sizeof(u_int8_t) * (gui->buffer.bufferWrite.usedSize));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "pin");
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[1]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[2]);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    funct_ressource_in_ia(gui, tmp_ia);
    gui->buffer.bufferWrite.octets[gui->buffer.bufferWrite.usedSize] = '\0';
}

void funct_server_pin(uint8_t **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);

    if (tmp_ia == NULL) {
        return;
    }
    funct_prepare_response(gui, tmp_ia, args);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_pin\n");
}
