/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** find_ia.c
*/

#include "zappy.h"

ia_t *to_find_ia(uint8_t *n, common_t *common)
{
    for (size_t i = 0; i < common->nb_ia; i++) {
        if (atoi((char*)n) == common->ia[i].player->id) {
            return &common->ia[i];
        }
    }
    return NULL;
}
