/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_ia.c
*/

#include "ia.h"
#include <stdlib.h>
#include "error_handling.h"

ia_t *set_ia(void)
{
    ia_t *ia = malloc(sizeof(ia_t) * MAX_PLAYER);
    if (ia == NULL)
        exit(error("Failed to allocate ia", 84));
    return ia;
}

void free_ia(ia_t *ia)
{
    free(ia);
    basic_log("Free ia", BLUE, 0);
}