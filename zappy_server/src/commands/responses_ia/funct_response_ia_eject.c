/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_eject
*/

#include "zappy.h"

//voir comment move les joueurs sur la plaques

static int find_ia_post(common_t *com, ia_t *ia)
{
    int i = 1;

    for (size_t i = 0; i < com->nb_ia; i++) {
        if (com->ia[i].player->x == ia->player->x && com->ia[i].player->y == ia->player->y) {
            i = 0;
        }
    }
    return i;
}

void funct_response_ia_eject(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    (void)com;
    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets, sizeof(u_int8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        //error
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '\0';
    if (find_ia_post(com, ia) == 0) {
        strcat((char*)ia->buffer.bufferWrite.octets, "ok\n\0");
    } else {
        strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets, ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_eject\n");
}
