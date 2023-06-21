/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_incantation
*/

#include "zappy.h"

//voir avec ludo pour l'incantation

static void funct_prepare_response_gui(ia_t *ia, common_t *com, int r)
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

static void funct_level_1(ia_t *ia, common_t *com)
{
    char buffer_incantation[256];

    ia->player->level += 1;
    sprintf(buffer_incantation, "%ld", ia->player->level);
    ia->buffer.bufferWrite.usedSize = 35 + strlen(buffer_incantation);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    char level[3];
    sprintf(level, "%ld", ia->player->level);
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)ia->buffer.bufferWrite.octets, "Elevation underway current level ");
    strcat((char*)ia->buffer.bufferWrite.octets, level);
    strcat((char*)ia->buffer.bufferWrite.octets, "\n\0");
    funct_prepare_response_gui(ia, com, 1);
}

static void funct_level_other_level(ia_t *ia, common_t *com, int nbr_ia_level)
{
    char buffer_incantation[256];
    ia_t *tmp_ia;

    for (int i = 0; i < nbr_ia_level; i++) {
        tmp_ia = to_find_ia_int(com->gui->map.tiles[ia->player->x][ia->player->y].nb_player_incantations[i], com);
        tmp_ia->player->level += 1;
    }
    sprintf(buffer_incantation, "%ld", ia->player->level);
    ia->buffer.bufferWrite.usedSize = 35 + strlen(buffer_incantation);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    char level[3];
    sprintf(level, "%ld", ia->player->level);
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)ia->buffer.bufferWrite.octets, "Elevation underway current level ");
    strcat((char*)ia->buffer.bufferWrite.octets, level);
    strcat((char*)ia->buffer.bufferWrite.octets, "\n\0");
    funct_prepare_response_gui(ia, com, 1);
}

void funct_response_ia_incantation(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    if (strcmp((char *)args[0], "ok")) {
        if (ia->player->level == 1) {
            funct_level_1(ia, com);
        } else if (ia->player->level == 2 || ia->player->level == 3) {
            funct_level_other_level(ia, com, 2);
        } else if (ia->player->level == 4 || ia->player->level == 5) {
            funct_level_other_level(ia, com, 4);
        } else {
            funct_level_other_level(ia, com, 6);
        }
    } else {
        ia->buffer.bufferWrite.usedSize = 4;
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        ia->buffer.bufferWrite.octets[0] = '\0';
        strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets, ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_incantation\n");
}
