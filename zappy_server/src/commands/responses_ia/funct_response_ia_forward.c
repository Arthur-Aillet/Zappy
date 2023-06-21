/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_forward
*/

#include "zappy.h"

static void to_move_ia(ia_t *ia, common_t *com)
{
    if (ia->player->orientation == North) {
        ia->player->y -= 1;
        if (ia->player->y < 0)
            ia->player->y = com->gui->map.height;
    }
    if (ia->player->orientation == Sud) {
        ia->player->y += 1;
        if (ia->player->y > com->gui->map.height)
            ia->player->y = 0;
    }
    if (ia->player->orientation == Est) {
        ia->player->x += 1;
        if (ia->player->x > com->gui->map.width)
            ia->player->x = 0;
    }
    if (ia->player->orientation == West) {
        ia->player->x -= 1;
        if (ia->player->x < 0)
            ia->player->x = com->gui->map.width;
    }
}

void funct_response_ia_forward(uint8_t **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    (void)com;

    to_move_ia(ia, com);
    ia->buffer.bufferWrite.usedSize = 4;
    ia->buffer.bufferWrite.octets = realloc(ia->buffer.bufferWrite.octets,
                    sizeof(uint8_t) * (ia->buffer.bufferWrite.usedSize));
    if (ia->buffer.bufferWrite.octets == NULL) {
        return;
    }
    ia->buffer.bufferWrite.octets[0] = '\0';
    strcat((char*)ia->buffer.bufferWrite.octets, "ok\n\0");
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets,
        ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_forward\n");
}
