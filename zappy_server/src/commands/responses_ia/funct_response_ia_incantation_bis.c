/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_incantation_bis
*/

#include "zappy.h"

static void funct_prepare_response_gui_next(ia_t *ia,
                                u_int8_t **args, common_t *com, int r)
{
    char buffer_args[256];

    sprintf(buffer_args, "%d", ia->player->y);
    args[1] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (args[1] == NULL) {
        return;
    }
    args[1][0] = '\0';
    strcat((char*)args[1], buffer_args);
    sprintf(buffer_args, "%d", r);
    args[1] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (args[1] == NULL) {
        return;
    }
    args[1][0] = '\0';
    strcat((char*)args[1], buffer_args);
    funct_server_pie(args, com->gui, com);
}

void funct_prepare_response_gui_incantation(ia_t *ia, common_t *com, int r)
{
    u_int8_t **args = malloc(sizeof(u_int8_t *) * 3);
    char buffer_args[256];

    if (args == NULL) {
        return;
    }
    sprintf(buffer_args, "%d", ia->player->x);
    args[0] = malloc(sizeof(u_int8_t) * strlen(buffer_args));
    if (args[0] == NULL) {
        return;
    }
    args[0][0] = '\0';
    strcat((char*)args[0], buffer_args);
    funct_prepare_response_gui_next(ia, args, com, r);
}

void funct_level_1(ia_t *ia, common_t *com)
{
    char buffer_incantation[256];

    ia->player->level += 1;
    sprintf(buffer_incantation, "%ld", ia->player->level);
    ia->buffer.bufferWrite.usedSize = 35 + strlen(buffer_incantation);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    char level[3];
    sprintf(level, "%ld", ia->player->level);
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)ia->buffer.bufferWrite.octets,
    "Elevation underway current level ");
    strcat((char*)ia->buffer.bufferWrite.octets, level);
    strcat((char*)ia->buffer.bufferWrite.octets, "\n\0");
    funct_prepare_response_gui_incantation(ia, com, 1);
    funct_server_seg(NULL, ia, com);
}
