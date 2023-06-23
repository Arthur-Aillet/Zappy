/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** find_ia.c
*/

#include "zappy.h"

ia_t *to_find_ia(char *n, common_t *common)
{
    if (n[0] == '#')
        n++;
    for (size_t i = 0; i < MAX_PLAYER; i++) {
        if (common->ia[i].player != NULL &&
        atoi(n) == common->ia[i].player->id) {
            return &common->ia[i];
        }
    }
    return NULL;
}

ia_t *to_find_ia_int(int n, common_t *common)
{
    for (size_t i = 0; i < MAX_PLAYER; i++) {
        if (common->ia[i].player != NULL &&
        n == common->ia[i].player->id) {
            return &common->ia[i];
        }
    }
    return NULL;
}
