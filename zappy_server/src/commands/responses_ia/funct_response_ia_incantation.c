/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_incantation
*/

#include "zappy.h"

static void funct_level_other_level_next(ia_t *ia, common_t *com)
{
    char level[3];

    sprintf(level, "%ld", ia->player->level);
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat(ia->buffer.bufferWrite.octets,
    "Elevation underway current level ");
    strcat(ia->buffer.bufferWrite.octets, level);
    strcat(ia->buffer.bufferWrite.octets, "\n\0");
    funct_prepare_response_gui_incantation(ia, com, 1);
}

static void funct_level_other_level(ia_t *ia, common_t *com, int nbr_ia_level)
{
    char buffer_incantation[256];
    ia_t *tmp_ia;

    for (int i = 0; i < nbr_ia_level; i++) {
        tmp_ia = to_find_ia_int(com->gui->map.tiles[ia->player->y]
        [ia->player->x].nb_player_incantations[i], com);
        tmp_ia->player->level += 1;
        funct_server_seg(NULL, tmp_ia, com);
    }
    sprintf(buffer_incantation, "%ld", ia->player->level);
    ia->buffer.bufferWrite.usedSize = 35 + strlen(buffer_incantation);
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(char) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    funct_level_other_level_next(ia, com);
}

static void funct_response_ia_incantation_bis(ia_t *ia, common_t *com)
{
    if (ia->player->level == 2 || ia->player->level == 3) {
            funct_level_other_level(ia, com, 2);
    }
    if (ia->player->level == 4 || ia->player->level == 5) {
        funct_level_other_level(ia, com, 4);
    }
    if (ia->player->level == 6 || ia->player->level == 7) {
        funct_level_other_level(ia, com, 6);
    }
}

static void funct_response_echec_incantation(ia_t *ia)
{
    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
    sizeof(char) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat(ia->buffer.bufferWrite.octets, "ko\n\0");
}

void funct_response_ia_incantation(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    if (strcmp(args[0], "ok") == 0) {
        if (ia->player->level == 1) {
            funct_level_1(ia, com);
        } else {
            funct_response_ia_incantation_bis(ia, com);
        }
    } else {
        funct_response_echec_incantation(ia);
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets,
    ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_incantation\n");
}
