/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_eject
*/

#include "zappy.h"

static egg_t *remove_egg(egg_t egg, egg_t *old_eggs, size_t nb_eggs, common_t *com)
{
    egg_t *new_eggs = malloc(sizeof(egg_t) * (nb_eggs - 1));
    size_t nb = 0;
    u_int8_t **args = malloc(sizeof(u_int8_t *) * 1);
    char buffer_egg[256];

    if (args == NULL) {
        //error
    }
    sprintf(buffer_egg, "%d", egg.egg_id);
    args[0] = malloc(sizeof(u_int8_t) * strlen(buffer_egg));
    if (args[0] == NULL) {
        //error
    }
    args[0][0] = '\0';
    strcat((char*)args[0], buffer_egg);

    if (new_eggs == NULL) {
        return NULL;
    }
    for (size_t tmp = 0; tmp < nb_eggs; tmp++) {
        if (egg.egg_id != old_eggs[tmp].egg_id) {
            new_eggs[tmp].egg_id = old_eggs[tmp].egg_id;
            new_eggs[tmp].x = old_eggs[tmp].x;
            new_eggs[tmp].y = old_eggs[tmp].y;
            nb++;
        }
    }
    funct_server_edi(args, com->gui, com);
    return new_eggs;
}

static void remove_player(player_t *ennemy, player_t *ia, common_t *com)
{
    u_int8_t **args = malloc(sizeof(u_int8_t *) * 1);
    char buffer_ennemy[256];

    if (args == NULL) {
        //error
    }
    sprintf(buffer_ennemy, "%d", ennemy->id);
    args[0] = malloc(sizeof(u_int8_t) * strlen(buffer_ennemy));
    if (args[0] == NULL) {
        //error
    }
    args[0][0] = '\0';
    strcat((char*)args[0], buffer_ennemy);
    if (ia->orientation == North) {
        if ((size_t)ennemy->x == com->gui->map.height) {
            ennemy->x = 0;
        } else {
            ennemy->x += 1;
        }
    }
    else if (ia->orientation == Est) {
        if (ennemy->y == 0) {
            ennemy->y = com->gui->map.width;
        } else {
            ennemy->y -= 1;
        }
    }
    else if (ia->orientation == Sud) {
        if (ennemy->x == 0) {
            ennemy->x = com->gui->map.height;
        } else {
            ennemy->x -= 1;
        }
    } else {
        if ((size_t)ennemy->y == com->gui->map.width) {
            ennemy->y = 0;
        } else {
            ennemy->y += 1;
        }
    }
    funct_server_pex(args, com->gui, com);
}

static int find_post(common_t *com, ia_t *ia)
{
    int i = 1;

    for (size_t i = 0; i < com->nb_ia; i++) {
        if (com->ia[i].player->x == ia->player->x && com->ia[i].player->y == ia->player->y) {
            remove_player(com->ia[i].player, ia->player, com);
            i = 0;
        }
    }
    for (size_t i = 0; i < com->nb_teams; i++) {
        for (size_t j = 0; j < com->teams[i].nb_eggs; j++) {
            if (com->teams[i].egg[j].x == ia->player->x && com->teams[i].egg[j].y == ia->player->y) {
                com->teams[i].egg = remove_egg(com->teams[i].egg[j], com->teams[i].egg, com->teams[i].nb_eggs, com);
                com->teams[i].nb_eggs -= 1;
                i = 0;
            }
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
    if (find_post(com, ia) == 0) {
        strcat((char*)ia->buffer.bufferWrite.octets, "ok\n\0");
    } else {
        strcat((char*)ia->buffer.bufferWrite.octets, "ko\n\0");
    }
    write(ia->buffer.sock.sockfd, ia->buffer.bufferWrite.octets, ia->buffer.bufferWrite.usedSize);
    printf("rentrer dans la fonctions funct_response_ia_eject\n");
}
