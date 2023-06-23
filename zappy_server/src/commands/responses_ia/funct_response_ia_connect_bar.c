/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_connect_bar
*/

#include "zappy.h"

void funct_response_ia_connect_bar(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    team_t *team = to_find_team_by_int(ia->player->id, com);
    char buffer_nb_slot[256];

    (void)args;
    sprintf(buffer_nb_slot, "%ld", team->nb_slot);
    ia->buffer.bufferWrite.usedSize = strlen(buffer_nb_slot) + 2;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                    sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)ia->buffer.bufferWrite.octets, buffer_nb_slot);
    strcat((char*)ia->buffer.bufferWrite.octets, "\n\0");
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets,
        ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_connect_bar\n");
}
