/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_ia.c
*/

#include "ia.h"
#include <stdlib.h>

ia_t *set_ia(void)
{
    ia_t *ia = malloc(sizeof(ia_t) * MAX_PLAYER);
    return ia;
}

void free_ia(ia_t *ia)
{
    free(ia);
}