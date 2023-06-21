/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_server_ppo
*/

#include "zappy.h"
#include <string.h>

static void funct_args_response(char *buffer_x, char *buffer_y,
                                char *buffer_o, gui_t *gui)
{
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, buffer_x);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, buffer_y);
    strcat((char*)gui->buffer.bufferWrite.octets, " ");
    strcat((char*)gui->buffer.bufferWrite.octets, buffer_o);
    strcat((char*)gui->buffer.bufferWrite.octets, "\n\0");
}

static void funct_prepare_response(gui_t *gui, uint8_t **args, ia_t *tmp_ia)
{
    char buffer_x[256];
    char buffer_y[256];
    char buffer_o[256];

    sprintf(buffer_x, "%d", tmp_ia->player->x);
    sprintf(buffer_y, "%d", tmp_ia->player->y);
    sprintf(buffer_o, "%ld", tmp_ia->player->orientation);
    gui->buffer.bufferWrite.usedSize += (strlen(buffer_x) + strlen(buffer_y)
    + strlen(buffer_o) + 9);
    gui->buffer.bufferWrite.octets = realloc(gui->buffer.bufferWrite.octets,
    sizeof(uint8_t) * (gui->buffer.bufferWrite.usedSize + 1));
    if (gui->buffer.bufferWrite.octets == NULL) {
        return;
    }
    gui->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)gui->buffer.bufferWrite.octets, "ppo ");
    strcat((char*)gui->buffer.bufferWrite.octets, (char*)args[0]);
    funct_args_response(buffer_x, buffer_y, buffer_o, gui);
}

void funct_server_ppo(uint8_t **args, void *info, common_t *common)
{
    gui_t *gui = (gui_t *)info;
    ia_t *tmp_ia = to_find_ia(args[0], common);

    if (tmp_ia == NULL) {
        return;
    }
    funct_prepare_response(gui, args, tmp_ia);
    write(gui->buffer.sock.sockfd, gui->buffer.bufferWrite.octets,
        gui->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_server_ppo\n");
}
