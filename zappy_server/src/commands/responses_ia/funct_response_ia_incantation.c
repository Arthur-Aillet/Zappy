/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_incantation
*/

#include "zappy.h"

//voir avec ludo pour l'incantation

void funct_response_ia_incantation(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;
    char buffer_incantation[256];

    (void)args;
    (void)com;
    if (1) {
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
    } else {
        ia->buffer.bufferWrite.usedSize = 4;
        ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
        if (ia->buffer.bufferWrite.octets == NULL) {
            return;
        }
        ia->buffer.bufferWrite.octets[0] = '\0';
        strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets, ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_incantation\n");
}
