/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_connect_nbr
*/

#include "zappy.h"

static team_t *to_find_team(int n, common_t *common)
{
    for (size_t i = 0; i < common->nb_teams; i++) {
        for (size_t y = 0; y < common->teams[i].actif_player; y++) {
            if (n == common->teams[i].players[y].id) {
                return &common->teams[i];
            }
        }
    }
    return NULL;
}

void funct_response_ia_connect_nbr(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    team_t *team = to_find_team(ia->player->id, com);
    char buffer_nb_slot[256];

    (void)args;
    sprintf(buffer_nb_slot, "%ld", team->nb_slot);
    ia->buffer.bufferWrite.usedSize = strlen(buffer_nb_slot) + 2;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_nb_slot);
    strcat((char*)ia->buffer.bufferWrite.octets, "\n\0");
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets, ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_connect_nbr\n");
}
